#include "World.h"
#include "converter.h"
#include "random.h"

namespace book
{
	World::World(int size_x, int size_y) : m_physicalWorld(b2Vec2(0.f, 1.5f)), m_x(size_x), m_y(size_y)
	{
		createWall(0, 0, BOOK_BOX_SIZE, m_y * BOOK_BOX_SIZE);
		createWall(BOOK_BOX_SIZE * (m_x + 1.2), 0, BOOK_BOX_SIZE, m_y * BOOK_BOX_SIZE);
		createWall(0, BOOK_BOX_SIZE * m_y, BOOK_BOX_SIZE * (m_x * 2.2), BOOK_BOX_SIZE);
	}

	World::~World()
	{
		for (b2Body* body = m_physicalWorld.GetBodyList(); body != nullptr;)
		{
			b2Body* next = body->GetNext();
			if (body->GetType() == b2_dynamicBody)
				delete reinterpret_cast<Piece*>(body->GetUserData().pointer);
			else
				delete reinterpret_cast<sf::RectangleShape*>(body->GetUserData().pointer);
			body = next;
		}
	}

	void World::update(sf::Time deltaTime)
	{
		for (b2Body* body = m_physicalWorld.GetBodyList(); body != nullptr; body = body->GetNext())
		{
			if (body->GetType() == b2_dynamicBody)
			{
				Piece* piece = reinterpret_cast<Piece*>(body->GetUserData().pointer);
				piece->update();
			}
		}
		m_sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {
				return sound->getStatus() != sf::SoundSource::Status::Playing;
			});
	}

	class _AABB_callback : public b2QueryCallback
	{
	public:
		std::list<b2Fixture*> fixtures;

		virtual bool ReportFixture(b2Fixture* fixture) override
		{
			if (fixture->GetBody()->GetType() == b2_dynamicBody)
				fixtures.emplace_back(fixture);
			return true;
		}
	};

	int World::clearLines(bool& del, const Piece& current)
	{
		int nb_lines = 0;
		_AABB_callback callback;
		del = false;
		for (int y = 0; y <= m_y; ++y)
		{
			// loop on Y axies
			b2AABB aabb; // world query
			// set the limit of the query
			aabb.lowerBound = b2Vec2(converter::pixelsToMeters<double>(0),
				converter::pixelsToMeters<double>((y + 0.49) * BOOK_BOX_SIZE));
			aabb.upperBound = b2Vec2(converter::pixelsToMeters<double>(m_x * BOOK_BOX_SIZE),
				converter::pixelsToMeters<double>((y + 0.51) * BOOK_BOX_SIZE));

			// query the world
			m_physicalWorld.QueryAABB(&callback, aabb);

			if ((int)callback.fixtures.size() >= m_x)
			{
				for (b2Fixture* fixture : callback.fixtures)
				{
					b2Body* body = fixture->GetBody();
					del |= body == current.getBody();
					if (body->GetFixtureList()->GetNext() != nullptr)
					{
						sf::ConvexShape* shape = reinterpret_cast<sf::ConvexShape*>(fixture->GetUserData().pointer);
						body->DestroyFixture(fixture);
						delete shape;
					}
					else
					{
						Piece* piece = reinterpret_cast<Piece*>(body->GetUserData().pointer);
						delete piece;
					}

					fixture = nullptr;
				}
				++nb_lines;
			}
			callback.fixtures.clear();
		}

		if (nb_lines > 0)
			add(Configuration::Sounds::Explosion);
		return nb_lines;
	}

	void World::updateGravity(int level)
	{
		m_physicalWorld.SetGravity(b2Vec2(0, 1.5 + (level / 2.0)));
	}

	void World::add(Configuration::Sounds sound_id)
	{
		std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(sound_id)));
		sound->setAttenuation(0);
		sound->play();
		m_sounds.emplace_back(std::move(sound));
	}

	bool World::isGameOver() const
	{
		for (const b2Body* body = m_physicalWorld.GetBodyList(); body != nullptr; body = body->GetNext())
		{
			if (body->GetType() == b2_staticBody)
				continue;
			if (body->GetPosition().y < 0)
				return true;
		}
		return false;
	}

	void World::updatePhysics(sf::Time deltaTime)
	{
		float seconds = deltaTime.asSeconds();
		m_physicalWorld.Step(seconds, 8, 3);
	}

	Piece* World::newPiece()
	{
		add(Configuration::Sounds::Spawn);
		return new Piece(m_physicalWorld,
			m_x / 2 * BOOK_BOX_SIZE, BOOK_BOX_SIZE,
			static_cast<Piece::TetriminoTypes>(random(0, Piece::TetriminoTypes::SIZE - 1)),
			random(0.f, 360.f));
	}
	
	void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const b2Body* body = m_physicalWorld.GetBodyList(); body != nullptr; body = body->GetNext())
		{
			if (body->GetType() == b2_dynamicBody)
			{
				Piece* piece = reinterpret_cast<Piece*>(body->GetUserData().pointer);
				target.draw(*piece, states);
			}
			else
			{
				sf::RectangleShape* shape = reinterpret_cast<sf::RectangleShape*>(body->GetUserData().pointer);
				target.draw(*shape, states);
			}
		}
	}
	
	void World::createWall(int pos_x, int pos_y, int size_x, int size_y)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(converter::pixelsToMeters<double>(pos_x), converter::pixelsToMeters<double>(pos_y));
		bodyDef.type = b2_staticBody;

		b2PolygonShape b2shape;
		double sx = converter::pixelsToMeters<double>(size_x) / 2.0;
		double sy = converter::pixelsToMeters<double>(size_y) / 2.0;
		b2shape.SetAsBox(sx, sy, b2Vec2(sx, sy), 0);

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.8;
		fixtureDef.restitution = 0.1;
		fixtureDef.shape = &b2shape;

		b2Body* body = m_physicalWorld.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(size_x, size_y));
		shape->setOrigin(size_x / 2.0, size_y / 2.0);
		shape->setPosition(sf::Vector2f(pos_x + size_x / 2.0, pos_y + size_y / 2.0));

		shape->setFillColor(sf::Color(50, 50, 50));

		body->GetUserData().pointer = (uintptr_t)shape;
	}
}