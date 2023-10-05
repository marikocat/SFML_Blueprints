#include "World.h"
#include "Entity.h"

namespace book
{
	World::World(float x, float y) : m_x(x), m_y(y){}
	World::~World() { clear(); }

	void World::clear()
	{
		for (Entity* entity : m_entities)
			delete entity;
		m_entities.clear();

		for (Entity* entity : m_entities_tmp)
			delete entity;
		m_entities_tmp.clear();

		m_sounds.clear();
	}

	void World::add(Entity* entity)
	{
		m_entities_tmp.push_back(entity);
	}
	void World::add(Configuration::Sounds sound_id)
	{
		std::unique_ptr<sf::Sound> sound(new
			sf::Sound(Configuration::sounds.get(sound_id)));
		sound->setAttenuation(0);
		sound->play();
		m_sounds.emplace_back(std::move(sound));
	}

	bool World::isCollide(const Entity& other)
	{
		for (Entity* entity_ptr : m_entities)
			if (other.isCollide(*entity_ptr))
				return true;
		return false;
	}

	int World::size() {return m_entities.size() + m_entities_tmp.size();}
	int World::getX() const { return m_x; }
	int World::getY() const { return m_y; }
	const std::list<Entity*> World::getEntities() const { return m_entities; }

	void World::update(sf::Time deltaTime)
	{
		if (m_entities_tmp.size() > 0)
			m_entities.splice(m_entities.end(), m_entities_tmp);

		for (Entity* entity_ptr : m_entities)
		{
			Entity& entity = *entity_ptr;
			entity.update(deltaTime);
			sf::Vector2f pos = entity.getPosition();
			if (pos.x < 0)
			{
				pos.x = m_x;
				pos.y = m_y - pos.y;
			}
			else if (pos.x > m_x)
			{
				pos.x = 0;
				pos.y = m_y - pos.y;
			}
			if (pos.y < 0)
				pos.y = m_y;
			else if (pos.y > m_y)
				pos.y = 0;
			entity.setPosition(pos);
		}

		const auto end = m_entities.end();
		for (auto it_i = m_entities.begin(); it_i != end; ++it_i)
		{
			Entity& entity_i = **it_i;
			auto it_j = it_i;
			it_j++;
			for (; it_j != end; ++it_j)
			{
				Entity& entity_j = **it_j;
				if (entity_i.isAlive() and entity_i.isCollide(entity_j))
					entity_i.onDestroy();
				if (entity_j.isAlive() and entity_j.isCollide(entity_i))
					entity_j.onDestroy();
			}
		}
		for (auto it = m_entities.begin(); it != m_entities.end();)
		{
			if (not (*it)->isAlive())
			{
				delete* it;
				it = m_entities.erase(it);
			}
			else
				++it;
		}
		m_sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool
		{
			return sound->getStatus() != sf::SoundSource::Status::Playing;
		});
	}

	void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (Entity* entity : m_entities)
			target.draw(*entity, states);
	}
}