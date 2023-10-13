#include "Piece.h"
#include "converter.h"

namespace book
{
	const sf::Color Piece::TetriminoColors[Piece::TetriminoTypes::SIZE] = {
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Cyan,
		sf::Color::Magenta,
		sf::Color::White,
		sf::Color(195,132,58)
	};

	Piece::Piece(b2World& world, int pos_x, int pos_y, 
		TetriminoTypes type, float rotation) : m_world(world)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(converter::pixelsToMeters<double>(pos_x),
			converter::pixelsToMeters<double>(pos_y));
		bodyDef.type = b2_dynamicBody;
		bodyDef.angle = converter::degToRad(rotation);
		m_body = world.CreateBody(&bodyDef);

		switch (type)
		{
		case TetriminoTypes::O:
		{
			createPart(0, 0, type);
			createPart(0, 1, type);
			createPart(1, 0, type);
			createPart(1, 1, type);
		} break;
		case TetriminoTypes::I:
		{
			createPart(0, 0, type);
			createPart(1, 0, type);
			createPart(2, 0, type);
			createPart(3, 0, type);
		} break;
		case TetriminoTypes::S:
		{
			createPart(0, 1, type);
			createPart(1, 1, type);
			createPart(1, 0, type);
			createPart(2, 0, type);
		} break;
		case TetriminoTypes::Z:
		{
			createPart(0, 0, type);
			createPart(1, 0, type);
			createPart(1, 1, type);
			createPart(2, 1, type);
		} break;
		case TetriminoTypes::L:
		{
			createPart(0, 1, type);
			createPart(0, 0, type);
			createPart(1, 0, type);
			createPart(2, 0, type);
		} break;
		case TetriminoTypes::J:
		{
			createPart(0, 0, type);
			createPart(1, 0, type);
			createPart(2, 0, type);
			createPart(2, 1, type);
		}break;
		case TetriminoTypes::T:
		{
			createPart(0, 0, type);
			createPart(1, 0, type);
			createPart(1, 1, type);
			createPart(2, 0, type);
		} break;
		default: break;
		}
		m_body->GetUserData().pointer = (uintptr_t)this;
		update();
	}
	Piece::~Piece()
	{
		for (b2Fixture* fixture = m_body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
		{
			sf::ConvexShape* shape = reinterpret_cast<sf::ConvexShape*>(fixture->GetUserData().pointer);
			fixture->GetUserData().pointer = (uintptr_t)nullptr;
			delete shape;
		}
		m_world.DestroyBody(m_body);
	}

	void Piece::update()
	{
		const b2Transform& xf = m_body->GetTransform();

		for (b2Fixture* fixture = m_body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
		{
			sf::ConvexShape* shape = reinterpret_cast<sf::ConvexShape*>(fixture->GetUserData().pointer);
			const b2PolygonShape* b2shape = static_cast<b2PolygonShape*>(fixture->GetShape());
			const uint32 count = b2shape->m_count;
			for (uint32 i = 0; i < count; ++i)
			{
				b2Vec2 vertex = b2Mul(xf, b2shape->m_vertices[i]);
				shape->setPoint(i, sf::Vector2f(converter::metersToPixels(vertex.x), converter::metersToPixels(vertex.y)));
			}
		}
	}

	void Piece::rotate(float angle)
	{
		m_body->ApplyTorque(converter::degToRad(angle), true);
	}

	void Piece::moveX(int direction)
	{
		m_body->ApplyForceToCenter(b2Vec2(converter::pixelsToMeters(direction), 0), true);
	}

	b2Body* Piece::getBody() const
	{
		return m_body;
	}

	void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const b2Fixture* fixture = m_body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
		{
			sf::ConvexShape* shape = reinterpret_cast<sf::ConvexShape*>(fixture->GetUserData().pointer);
			if (shape)
				target.draw(*shape, states);
		}
	}

	b2Fixture* Piece::createPart(int pos_x, int pos_y, TetriminoTypes type)
	{
		b2PolygonShape b2shape;
		b2shape.SetAsBox(converter::pixelsToMeters<double>(BOOK_BOX_SIZE_2),
			converter::pixelsToMeters<double>(BOOK_BOX_SIZE_2),
			b2Vec2(converter::pixelsToMeters<double>(BOOK_BOX_SIZE_2 + pos_x * BOOK_BOX_SIZE),
				converter::pixelsToMeters<double>(BOOK_BOX_SIZE_2 + pos_y * BOOK_BOX_SIZE)), 0);

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.5;
		fixtureDef.restitution = 0.4;
		fixtureDef.shape = &b2shape;

		b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);
		sf::ConvexShape* shape = new sf::ConvexShape((unsigned int)b2shape.m_count);
		shape->setFillColor(TetriminoColors[type]);
		shape->setOutlineThickness(1.0f);
		shape->setOutlineColor(sf::Color(128, 128, 128));
		fixture->GetUserData().pointer = (uintptr_t)shape;

		return fixture;
	}
}