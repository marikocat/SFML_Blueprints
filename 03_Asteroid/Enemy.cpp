#define _USE_MATH_DEFINES
#include <cmath>
#include "Enemy.h"
#include "Random.h"

namespace book
{
	Enemy::Enemy(Configuration::Textures tex_id, World& world) : Entity(tex_id, world)
	{
		float angle = random(0.f, 2.f * M_PI);
		m_impulse = sf::Vector2f(std::cos(angle), std::sin(angle));
	}

	void Enemy::onDestroy()
	{
		Entity::onDestroy();
		Configuration::addScore(getPoints());
	}
}