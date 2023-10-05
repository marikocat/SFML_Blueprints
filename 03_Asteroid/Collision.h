#pragma once
#include <SFML/Graphics.hpp>

namespace book
{
	class Collision
	{
	public:
		Collision() = delete;
		Collision(const Collision&) = delete;
		Collision& operator=(const Collision&) = delete;
		static bool circleTest(const sf::Sprite& first, const sf::Sprite& second);
	};
}