#pragma once
#include "SFML/Graphics.hpp"
#include <utility>
#include "ActionTarget.h"

namespace book
{
	class Player : public sf::Drawable, public ActionTarget<int>
	{
	public:
		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;

		Player();

		template<typename ... Args>
		void setPosition(Args&& ... args);

		void processEvents();
		void update(sf::Time deltaTime);	
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		sf::Sprite m_ship;
		sf::Vector2f m_velocity;

		bool m_isMoving;
		int m_rotation;
	};
}

#include "Player.tpl"