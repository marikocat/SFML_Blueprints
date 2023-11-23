#pragma warning(disable : 4996)

#include <SFML-Book/Level.h>

#include <SFML-Book/System.h>
#include <SFML-Book/Component.h>

#include <stdexcept>
#include <ctime>

namespace book
{
	Level::FuncType Level::defaultFunc = [](Level::Param&) {};

	Level::Level(sf::RenderWindow& window, const std::string& filename) :
		onPickup(defaultFunc),
		_map(sfutils::VMap::createMapFromFile(filename)),
		_viewer(window, *_map, Configuration::mapInputs),
		_mouseLayer(new sfutils::Layer<sf::ConvexShape>("ConvexShape", 1)),
		_entitiesLayer(new sfutils::Layer<Entity*>("Entity", 2))
	{
		// Map
		if (_map == nullptr)
		{
			// error
			throw std::runtime_error("Impossible to load file " + filename);
		}

		// mouse layer
		{
			_mouse_light = _mouseLayer->add(_map->getShape());
			_mouse_light->setFillColor(sf::Color(255, 255, 255, 64));
			_map->add(_mouseLayer);
		}

		// entities layer
		_map->add(_entitiesLayer);

		// Viewer
		_viewer.bind(Configuration::MapInputs::TakeScreen, [&window](const sf::Event& event)
			{
				sf::Vector2u windowSize = window.getSize();
				sf::Texture texture;
				texture.create(windowSize.x, windowSize.y);
				texture.update(window);
				sf::Image screenshot = texture.copyToImage();

				time_t rawtime;
				struct tm* timeinfo;
				char buffer[128];

				std::time(&rawtime);
				timeinfo = std::localtime(&rawtime);
				std::strftime(buffer, 128, "screen/%F_%T.png", timeinfo);
				std::string file_name(buffer);
				std::replace(file_name.begin(), file_name.end(), ':', '-');
				screenshot.saveToFile(file_name);
			});

		// Systems
		systems.add<SysAIMain>();
		systems.add<SysAIWarrior>(*this);
		systems.add<SysAIDefender>(*this);
		systems.add<SysAISpawner>(*this);
		systems.add<SysAIWalker>(*this);
		systems.add<SysAIFlyer>(*this);
		systems.add<SysSkin>();
		systems.add<SysHp>(*this);
		systems.add<SysEffect>(*this);
	}

	Level::~Level()
	{
		entities.reset();
		delete _map;
	}

	void Level::update(sf::Time deltaTime)
	{
		_viewer.update(deltaTime.asSeconds());
		Application::update(deltaTime);
		_entitiesLayer->sort();

		sf::Vector2f pos = _viewer.getPosition();

		sf::Listener::setPosition(pos.x, pos.y, _viewer.getZoom());

		_sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound)->bool
			{
				return sound->getStatus() != sf::SoundSource::Status::Playing;
			});
	}

	bool Level::processEvent(sf::Event& event)
	{
		bool res = _viewer.processEvent(event);

		if (not res)
		{
			if (event.type == sf::Event::EventType::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Button::Left)
			{
				sf::Vector2i coord = _viewer.mapScreenToCoords(event.mouseButton.x, event.mouseButton.y);
				std::list<Entity*> pick = getByCoords(coord);
				for (Entity* e : pick)
				{
					Param p(coord, *e, *_entitiesLayer, *_map);
					onPickup(p);
				}
			}
			else if (event.type == sf::Event::EventType::MouseMoved)
			{
				sf::Vector2i coord = _viewer.mapScreenToCoords(event.mouseMove.x, event.mouseMove.y);
				sf::Vector2f pos = _viewer.mapCoordsToPixel(coord.x, coord.y);
				_mouse_light->setPosition(pos);
			}
		}

		return res;
	}

	void Level::processEvents()
	{
		_viewer.processEvents();
	}

	void Level::draw(sf::RenderTarget& window)
	{
		_viewer.draw();
	}

	Level::Param::Param(sf::Vector2i& c, Entity& e, sfutils::Layer<Entity*>& l, sfutils::VMap& m)
		: coord(c), entity(e), layer(l), map(m)
	{
	}

	sfutils::EntityManager<Entity>& Level::entityManager()
	{
		return entities;
	}

	sfutils::Layer<sf::ConvexShape>& Level::getHighlightLayer() const
	{
		return *_mouseLayer;
	}

	const sf::ConvexShape Level::getShape() const
	{
		return _map->getShape();
	}

	Entity& Level::createEntity(const sf::Vector2i& coord)
	{
		std::uint32_t id = entities.create();
		Entity& e = entities.get(id);

		e.add<CompSkin>();
		e.setPosition(_map->mapCoordsToPixel(coord));

		_entitiesLayer->add(&e);
		_byCoords[coord].emplace_back(&e);

		return e;
	}

	void Level::destroyEntity(Entity& e)
	{
		const sf::Vector2i coord = mapPixelToCoords(entities.getComponent<CompSkin>(e.id())->_sprite.getPosition());

		_entitiesLayer->remove(&e, false);

		_byCoords[coord].remove(&e);
		e.remove();
	}

	void Level::destroyEntity(std::uint32_t id)
	{
		const sf::Vector2i coord = mapPixelToCoords(entities.getComponent<CompSkin>(id)->_sprite.getPosition());
		Entity& e = entities.get(id);

		_entitiesLayer->remove(&e, false);

		_byCoords[coord].remove(&e);
		e.remove();
	}

	void Level::setPosition(Entity& e, const sf::Vector2i& old, const sf::Vector2i& n)
	{
		if (n != old)
		{
			_byCoords[old].remove(&e);
			_byCoords[n].emplace_back(&e);
		}
	}

	void Level::createSound(Configuration::Sounds sound_id, const sf::Vector2i& coord)
	{
		sf::Vector2f pos = _map->mapCoordsToPixel(coord);
		createSound(sound_id, pos);
	}

	void Level::createSound(Configuration::Sounds sound_id, const sf::Vector2f& pos)
	{
		std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(sound_id)));
		sound->setPosition(pos.x, pos.y, 0);
		sound->setRelativeToListener(true);
		sound->setVolume(50);
		sound->setAttenuation(1);

		sound->play();
		_sounds.emplace_back(std::move(sound));
	}

	sf::Vector2i Level::mapPixelToCoords(const sf::Vector2f& pos) const
	{
		return _map->mapPixelToCoords(pos);
	}

	sf::Vector2f Level::mapCoordsToPixel(const sf::Vector2i& pos) const
	{
		return _map->mapCoordsToPixel(pos);
	}

	sf::Vector2i Level::mapCoordsToScreen(const sf::Vector2i& pos) const
	{
		return _viewer.mapCoordsToScreen(pos);
	}

	sf::Vector2i Level::mapScreenToCoords(const sf::Vector2i& pos) const
	{
		return _viewer.mapScreenToCoords(pos);
	}

	std::list<Entity*> Level::getByCoords(const sf::Vector2i& coord)
	{
		return _byCoords[coord];
	}

	std::list<sf::Vector2i> Level::getPath(const sf::Vector2i& origin, const sf::Vector2i& dest) const
	{
		return _map->getPath(origin, dest);
	}

	sf::Vector2i Level::getPath1(const sf::Vector2i& origin, const sf::Vector2i& dest) const
	{
		return _map->getPath1(origin, dest);
	}

	int Level::getDistance(const sf::Vector2i& origin, const sf::Vector2i& dest) const
	{
		return _map->getDistance(origin, dest);
	}

	sf::Vector2i Level::getMinCoord() const
	{
		return sf::Vector2i(0, 0);
	}

	sf::Vector2i Level::getMaxCoord() const
	{
		return sf::Vector2i(99, 99);
	}
}