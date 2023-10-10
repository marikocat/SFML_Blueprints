#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(400,
		400), "01_Introduction");
	window.setFramerateLimit(60);
	//create a circle
	sf::CircleShape circle(150);
	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(10, 20);
	//game loop
	while (window.isOpen())
	{
		//manage the events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed)
				or (event.type == sf::Event::KeyPressed and
					event.key.code == sf::Keyboard::Escape))
				window.close(); //close the window
		}
		window.clear(); //clear the windows to black
		window.draw(circle); //draw the circle
		window.display(); //display the result on screen
	}
	return 0;
}