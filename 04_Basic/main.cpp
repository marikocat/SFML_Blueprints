#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "converter.h"

#include <list>

namespace book
{
	b2Body* createBox(b2World& world, int pos_x, int pos_y, int size_x, int size_y, 
		b2BodyType type = b2_dynamicBody)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(converter::pixelsToMeters<double>(pos_x),
							converter::pixelsToMeters<double>(pos_y));
		bodyDef.type = type;

		b2PolygonShape b2shape;
		b2shape.SetAsBox(converter::pixelsToMeters<double>(size_x / 2.0),
						converter::pixelsToMeters<double>(size_y / 2.0));

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.4;
		fixtureDef.restitution = 0.5;
		fixtureDef.shape = &b2shape;

		b2Body* res = world.CreateBody(&bodyDef);
		res->CreateFixture(&fixtureDef);

		sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(size_x, size_y));
		shape->setOrigin(size_x / 2.0, size_y / 2.0);
		shape->setPosition(sf::Vector2f(pos_x, pos_y));
		if (type == b2_dynamicBody)
			shape->setFillColor(sf::Color::Blue);
		else
			shape->setFillColor(sf::Color::White);

		res->GetUserData().pointer = (uintptr_t)shape;

		return res;
	}

	void displayWorld(b2World& world, sf::RenderWindow& render)
	{
		world.Step(1.0 / 60, int32(8), int32(3));
		render.clear();

		for (b2Body* body = world.GetBodyList(); body != nullptr; body = body->GetNext())
		{
			sf::Shape* shape = reinterpret_cast<sf::Shape*>(body->GetUserData().pointer);
			shape->setPosition(converter::metersToPixels(body->GetPosition().x),
							converter::metersToPixels(body->GetPosition().y));
			shape->setRotation(converter::radToDeg<double>(body->GetAngle()));
			render.draw(*shape);
		}

		render.display();
	}
}

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "04_Basic");
	window.setFramerateLimit(60);

	b2Vec2 gravity(0.f, 9.8f);
	b2World world(gravity);

	std::list<b2Body*>bodies;
	bodies.emplace_back(book::createBox(world, 400, 590, 800, 20, b2_staticBody));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;
			bodies.emplace_back(book::createBox(world, x, y, 32, 32));
		}
		book::displayWorld(world, window);
	}

	for (b2Body* body : bodies)
	{
		delete reinterpret_cast<sf::RectangleShape*>(body->GetUserData().pointer);
		world.DestroyBody(body);
	}
	return 0;
}