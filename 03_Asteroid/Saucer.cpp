#include "Saucer.h"
#include "Random.h"
#include "Shoot.h"
#include "Meteor.h"
#include "Collision.h"
#include "World.h"
#include "Player.h"

#include <cfloat>

namespace book
{
	Saucer::Saucer(Configuration::Textures textures, World& world) : Enemy(textures, world)
	{

	}

	bool Saucer::isCollide(const Entity& other) const
	{
		if (dynamic_cast<const ShootSaucer*>(&other) == nullptr)
		{
			return Collision::circleTest(m_sprite, other.m_sprite);
		}
		return false;
	}

	void Saucer::update(sf::Time deltaTime)
	{
		float seconds = deltaTime.asSeconds();
		Entity* near = nullptr;
		float near_distance = 300;
		for (Entity* entity_ptr : m_world.getEntities())
		{
			if (entity_ptr != this and
				(dynamic_cast<const Meteor*>(entity_ptr) or dynamic_cast<const ShootPlayer*>(entity_ptr)))
			{
				float x = getPosition().x - entity_ptr->getPosition().x;
				float y = getPosition().y - entity_ptr->getPosition().y;
				float dist = std::sqrt(x * x + y * y);
				if (dist < near_distance)
				{
					near_distance = dist;
					near = entity_ptr;
				}
			}
		}

		if (near != nullptr)
		{
			sf::Vector2f pos = near->getPosition() - getPosition();
			float angle_rad = std::atan2(pos.y, pos.x);
			m_impulse -=
				sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 300.f * seconds;
		}
		else
		{
			sf::Vector2f pos = Configuration::player->getPosition() - getPosition();
			float angle_rad = std::atan2(pos.x, pos.y);
			m_impulse +=
				sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 100.f * seconds;
		}
		m_sprite.move(seconds * m_impulse);
	}

	void Saucer::onDestroy()
	{
		Enemy::onDestroy();
		m_world.add(Configuration::Sounds::Boom2);
	}

	void Saucer::newSaucer(World& world)
	{
		Saucer* res = nullptr;
		if (random(0.f, 1.f) > Configuration::getScore() / 40.f)
			res = new BigSaucer(world);
		else
			res = new SmallSaucer(world);
		res->setPosition(random(0, 1) * world.getX(),
			random(0.f, (float)world.getY()));
		world.add(res);
	}

	// Big saucer
	BigSaucer::BigSaucer(World& world) :
		Saucer(Configuration::Textures::SmallSaucer, world)
	{
		m_world.add(Configuration::Sounds::SaucerSpawn1);
		m_impulse *= 300.f;
	}

	int BigSaucer::getPoints() const { return 50; }

	// Small saucer
	SmallSaucer::SmallSaucer(World& world) :
		Saucer(Configuration::Textures::SmallSaucer, world)
	{
		m_timeSinceLastShoot = sf::Time::Zero;
		m_world.add(Configuration::Sounds::SaucerSpawn2);
		m_impulse *= 400.f;
	}

	int SmallSaucer::getPoints() const { return 200; }

	void SmallSaucer::update(sf::Time deltaTime)
	{
		Saucer::update(deltaTime);
		//shoot on the Configuration::player
		m_timeSinceLastShoot += deltaTime;
		if (m_timeSinceLastShoot > sf::seconds(1.5))
		{
			if (Configuration::player != nullptr)
				m_world.add(new ShootSaucer(*this));
			m_timeSinceLastShoot = sf::Time::Zero;
		}
	}
}