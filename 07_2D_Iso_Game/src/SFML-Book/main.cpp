#include "SFML-Book/Configuration.h"
#include "SFML-Book/Game.h"

//#include <SFML-utils/map/VMap.h>
//#include <SFML-utils/map/MapViewer.h>

#include <iostream>

using namespace sfutils;

int main(int argc, char* argv[])
{
	book::Configuration::initialize();

	book::Game game(1600, 900);
	game.load("./media/map.json");
	game.run();

	return 0;
}

/*// Creation of the window
	sf::RenderWindow window(sf::VideoMode(600, 800), "Example animation");

	// load the texture
	ResourceManager<sf::Texture, int> textures;
	textures.load(0, "media/img/eye.png");

	// Creation of the different animations
	Animation walkLeft(&textures.get(0));
	walkLeft.addFramesLine(4, 2, 0);
	Animation walkRight(&textures.get(0));
	walkRight.addFramesLine(4, 2, 1);

	//Creation of the animated sprite
	AnimatedSprite sprite(&walkLeft, AnimatedSprite::Playing, sf::seconds(0.1));

	// game loop
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time delta = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float speed = 50;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite.setAnimation(&walkLeft);
			sprite.play();
			sprite.move(-speed * delta.asSeconds(), 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.setAnimation(&walkRight);
			sprite.play();
			sprite.move(speed * delta.asSeconds(), 0);
		}

		window.clear();

		sprite.update(delta);
		window.draw(sprite);

		window.display();
	}*/

	// Creation of the window
		//sf::RenderWindow window(sf::VideoMode(1600, 900), "Example Tile");

		//sfutils::map::VMap* map = sfutils::map::VMap::createMapFromFile("./map.json");
		//sfutils::map::MapViewer viewer(window, *map);

		//sf::Texture tex;
		//if (tex.loadFromFile("media/img/ground.png")) std::cout << "texture loaded\n";
		//tex.setRepeated(true);

		//sfutils::map::Tile<sfutils::geometry::HexaIso> tile(5, 5, 50);
		//tile.setTexture(&tex, false);
		//tile.setTextureRect(sfutils::geometry::HexaIso::getTextureRect(10, 10, 50));

		//sf::FloatRect tile_bounds = tile.getGlobalBounds();
		//std::cout << tile_bounds.getSize().x << " " << tile_bounds.getSize().y << "\n";
		//std::cout << tile_bounds.getPosition().x << " " << tile_bounds.getPosition().y << "\n";

		//const float PI = 3.14159265;
		//const float sin_75 = sin(75 * PI / 180);
		//const float sin_15 = sin(15 * PI / 180);
		//const float sin_45 = sin(45 * PI / 180);
		//const float height = sin_15 + sin_45 + sin_75;
		//const float delta_x = sin_45 - sin_15;
		//const float delta_y = sin_75 + sin_45;
		//sf::ConvexShape _shape;
		//_shape.setPointCount(6);
		//_shape.setPoint(0, sf::Vector2f(0, (sin_15 + sin_75) / 2));
		//_shape.setPoint(1, sf::Vector2f(sin_15, sin_15 / 2));
		//_shape.setPoint(2, sf::Vector2f(sin_15 + sin_75, 0));
		//_shape.setPoint(3, sf::Vector2f(sin_15 + sin_75 + sin_45, sin_45 / 2));
		//_shape.setPoint(4, sf::Vector2f(sin_75 + sin_45, (sin_75 + sin_45) / 2));
		//_shape.setPoint(5, sf::Vector2f(sin_45, (sin_15 + sin_75 + sin_45) / 2));
		//_shape.setOrigin(height / 2, height / 4);
		//sf::FloatRect bounds = _shape.getGlobalBounds();
		//std::cout << "size of shape " << bounds.getSize().x << " " << bounds.getSize().y << "\n";

		//sf::ConvexShape _shape2 = _shape;
		//_shape2.setTexture(&tex, false);
		//_shape2.setTextureRect(sfutils::geometry::HexaIso::getTextureRect(10, 10, 50));
		//_shape2.setOutlineColor(sf::Color(255, 255, 255, 125));
		//_shape2.setOutlineThickness(2.f / 50);
		//_shape2.setScale(50, 50);
		//_shape2.setPosition(800, 450);
		//sf::FloatRect bounds2 = _shape2.getGlobalBounds();
		//std::cout << "size of shape 2 " << bounds2.getSize().x << " " << bounds2.getSize().y << "\n";
		//std::cout << "position of shape 2 " << bounds2.getPosition().x << " " << bounds2.getPosition().y << "\n";

		//// game loop
		//sf::Clock clock;
		//while (window.isOpen())
		//{
		//	sf::Event event;
		//	while (window.pollEvent(event))
		//	{
		//		if (event.type == sf::Event::Closed)
		//			window.close();
		//	}

		//	window.clear();

		//	viewer.processEvents();
		//	viewer.update(clock.restart().asSeconds());
		//	viewer.draw();

		//	window.display();
		//}