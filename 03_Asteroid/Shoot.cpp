#define _USE_MATH_DEFINES
#include <cmath>
#include "Shoot.h"
#include "Enemy.h"
#include "Saucer.h"
#include "Random.h"
#include "Collision.h"
#include "Player.h"
#include "Meteor.h"
#include "World.h"

namespace book
{
	Shoot::Shoot(Configuration::Textures tex_id, World& world) : Entity(tex_id, world)
	{
		float angle = random(0.f, 2.f * M_PI);
		m_impulse = sf::Vector2f(std::cos(angle), std::sin(angle));
	}

	void Shoot::update(sf::Time deltaTime)
	{
		float seconds = deltaTime.asSeconds();
		m_sprite.move(seconds * m_impulse);
		m_duration -= deltaTime;
		if (m_duration < sf::Time::Zero)
			m_alive = false;
	}

	// Shoot player

	ShootPlayer::ShootPlayer(Player& from) : 
		Shoot(Configuration::Textures::ShootPlayer, from.m_world)
	{
		m_duration = sf::seconds(5);

		float angle = from.m_sprite.getRotation() / 180 * M_PI - M_PI / 2;
		m_impulse = sf::Vector2f(std::cos(angle), std::sin(angle)) * 500.f;

		setPosition(from.getPosition());
		m_sprite.setRotation(from.m_sprite.getRotation());
		m_world.add(Configuration::Sounds::LaserPlayer);
	}

	bool ShootPlayer::isCollide(const Entity& other) const
	{
		if (dynamic_cast<const Enemy*>(&other) != nullptr)
		{
			return Collision::circleTest(m_sprite, other.m_sprite);
		}
		return false;
	}

	// Shoot saucer
	ShootSaucer::ShootSaucer(SmallSaucer& from) :
		Shoot(Configuration::Textures::ShootSaucer, from.m_world)
	{
		m_duration = sf::seconds(5);
		sf::Vector2f pos = Configuration::player->getPosition() - from.getPosition();
		float accuracy_lost = random(-1.f, 1.f) * M_PI / ((200 + Configuration::getScore()) / 100.f);
		float angle_rad = std::atan2(pos.y, pos.x) + accuracy_lost;
		float angle_deg = angle_rad * 180 / M_PI;

		m_impulse = sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 500.f;
		setPosition(from.getPosition());
		m_sprite.setRotation(angle_deg + 90);
		m_world.add(Configuration::Sounds::LaserEnemy);
	}

	bool ShootSaucer::isCollide(const Entity& other)const
	{
		if (dynamic_cast<const Player*>(&other) or dynamic_cast<const Meteor*>(&other))
		{
			return Collision::circleTest(m_sprite, other.m_sprite);
		}
		return false;
	}
}