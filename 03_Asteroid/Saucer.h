#pragma once
#include "Enemy.h"

namespace book
{
	class Saucer : public Enemy
	{
	public:
		Saucer(const Saucer&) = delete;
		Saucer& operator=(const Saucer&) = delete;
		Saucer(Configuration::Textures textures, World& world);

		using Enemy::Enemy;

		virtual bool isCollide(const Entity& other) const;
		virtual void update(sf::Time deltaTime);
		virtual void onDestroy();
		static void newSaucer(World& world);
	};

	class BigSaucer : public Saucer
	{
	public:
		BigSaucer(World& world);
		virtual int getPoints() const;
	};

	class SmallSaucer : public Saucer
	{
	public:
		SmallSaucer(World& world);
		virtual int getPoints() const;
		virtual void update(sf::Time deltaTime);
	private:
		sf::Time m_timeSinceLastShoot;
	};
}