#pragma once
#include <SFML/Graphics.hpp>

#include "ActionTarget.h"
#include "Entity.h"

namespace book
{
	class Player : public Entity, public ActionTarget<int>
	{
	public:
		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;

		Player(World& world);

		virtual bool isCollide(const Entity& other) const;
		virtual void update(sf::Time deltaTime);

		void processEvents();

		void shoot();
		void goToHyperspace();
		virtual void onDestroy();
	private:
		bool m_isMoving;
		int m_rotation;
		sf::Time m_timeSinceLastShoot;
	};
}