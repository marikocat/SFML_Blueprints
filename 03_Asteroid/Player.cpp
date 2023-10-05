#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.h"
#include "Random.h"
#include "Configuration.h"
#include "Collision.h"
#include "World.h"
#include "Shoot.h"

namespace book
{
	Player::Player(World& world) : Entity(Configuration::Textures::Player, world)
						,ActionTarget(Configuration::playerInputs)
						,m_isMoving(false)
						,m_rotation(0)
	{
		bind(Configuration::PlayerInputs::Up, [this](const sf::Event&) {
			m_isMoving = true; });

		bind(Configuration::PlayerInputs::Left, [this](const sf::Event&) {
			m_rotation -= 1; });

		bind(Configuration::PlayerInputs::Right, [this](const sf::Event&) {
			m_rotation += 1; });

		bind(Configuration::PlayerInputs::Shoot, [this](const sf::Event&) {
			shoot(); });

		bind(Configuration::PlayerInputs::Hyperspace, [this](const sf::Event&) {
			goToHyperspace(); });
	}

	bool Player::isCollide(const Entity& other) const
	{
		if (dynamic_cast<const ShootPlayer*>(&other) == nullptr)
		{
			return Collision::circleTest(m_sprite, other.m_sprite);
		}
		return false;
	}

	void Player::update(sf::Time deltaTime)
	{
		float seconds = deltaTime.asSeconds();
		m_timeSinceLastShoot += deltaTime;
		if (m_rotation != 0)
		{
			float angle = m_rotation * 250 * seconds;
			m_sprite.rotate(angle);
		}

		if (m_isMoving)
		{
			float angle = m_sprite.getRotation() / 180 * M_PI - M_PI / 2;
			m_impulse += sf::Vector2f(std::cos(angle), std::sin(angle)) * 300.f * seconds;
		}

		m_sprite.move(seconds * m_impulse);
	}

	void Player::processEvents()
	{
		m_isMoving = false;
		m_rotation = 0;
		ActionTarget::processEvents();
	}

	void Player::shoot()
	{
		if (m_timeSinceLastShoot > sf::seconds(0.3))
		{
			m_world.add(new ShootPlayer(*this));
			m_timeSinceLastShoot = sf::Time::Zero;
		}
	}

	void Player::goToHyperspace()
	{
		m_impulse = sf::Vector2f(0, 0);
		setPosition(random(0, m_world.getX()), random(0, m_world.getY()));
		m_world.add(Configuration::Sounds::Jump);
	}

	void Player::onDestroy()
	{
		Entity::onDestroy();
		Configuration::player = nullptr;
		Configuration::lives--;
		m_world.add(Configuration::Sounds::Boom);
	}
}