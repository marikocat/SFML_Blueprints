#include "Meteor.h"
#include "Random.h"
#include "Collision.h"
#include "World.h"

namespace book
{
	Meteor::Meteor(Configuration::Textures textures, World& world) :Enemy(textures, world)
	{

	}

	bool Meteor::isCollide(const Entity& other) const
	{
		if (dynamic_cast<const Meteor*>(&other) == nullptr)
		{
			return Collision::circleTest(m_sprite, other.m_sprite);
		}
		return false;
	}

	void Meteor::update(sf::Time deltaTime)
	{
		float seconds = deltaTime.asSeconds();
		m_sprite.move(seconds * m_impulse);
	}

	// Big meteor

	BigMeteor::BigMeteor(World& world) :
		Meteor((Configuration::Textures)random
		(Configuration::Textures::BigMeteor1, Configuration::Textures::BigMeteor4), world)
	{
		m_impulse *= 100.f;
	}

	int BigMeteor::getPoints()const { return 20; }

	void BigMeteor::onDestroy()
	{
		Meteor::onDestroy();
		int nb = book::random(2, 3);
		for (int i = 0; i < nb; ++i)
		{
			MediumMeteor* meteor = new MediumMeteor(m_world);
			meteor->setPosition(getPosition());
			m_world.add(meteor);
		}
		m_world.add(Configuration::Sounds::Explosion1);
	}

	// Medium meteor

	MediumMeteor::MediumMeteor(World& world) :
		Meteor((Configuration::Textures)random
		(Configuration::Textures::MediumMeteor1, Configuration::Textures::MediumMeteor2), world)
	{
		m_impulse *= 200.f;
	}

	int MediumMeteor::getPoints()const { return 60; }

	void MediumMeteor::onDestroy()
	{
		Meteor::onDestroy();
		int nb = book::random(2, 3);
		for (int i = 0; i < nb; ++i)
		{
			SmallMeteor* meteor = new SmallMeteor(m_world);
			meteor->setPosition(getPosition());
			m_world.add(meteor);
		}
		m_world.add(Configuration::Sounds::Explosion2);
	}

	// Small meteor

	SmallMeteor::SmallMeteor(World& world) :
		Meteor((Configuration::Textures)random
		(Configuration::Textures::SmallMeteor1, Configuration::Textures::SmallMeteor4), world)
	{
		m_impulse *= 300.f;
	}

	int SmallMeteor::getPoints() const { return 100; }

	void SmallMeteor::onDestroy()
	{
		Meteor::onDestroy();
		m_world.add(Configuration::Sounds::Explosion3);
	}
}