#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.h"
#include "Configuration.h"

#include <iostream>

namespace book
{
	Player::Player() : ActionTarget(Configuration::playerInputs)
						,m_isMoving(false)
						,m_rotation(0)
	{
		m_ship.setTexture(Configuration::textures.get(Configuration::Textures::Player));
		m_ship.setOrigin(49.5, 37.5);

		bind(Configuration::PlayerInputs::Up, [this](const sf::Event&) {
			m_isMoving = true; });

		bind(Configuration::PlayerInputs::Left, [this](const sf::Event&) {
			m_rotation -= 1; });

		bind(Configuration::PlayerInputs::Right, [this](const sf::Event&) {
			m_rotation += 1; });
	}

	void Player::processEvents()
	{
		m_isMoving = false;
		m_rotation = 0;
		ActionTarget::processEvents();
	}

	void Player::update(sf::Time deltaTime)
	{
		float seconds = deltaTime.asSeconds();
		if (m_rotation != 0)
		{
			float angle = m_rotation * 180 * seconds;
			m_ship.rotate(angle);
		}
		if (m_isMoving)
		{
			float angle = m_ship.getRotation() / 180 * M_PI - M_PI / 2;
			//std::cout << seconds << " " << std::cos(angle) << "\n";
			m_velocity += sf::Vector2f(std::cos(angle), std::sin(angle)) * 60.f * seconds; // uneven velocity
			//std::cout << m_velocity.x << " " << m_velocity.y << "\n";
		}
		m_ship.move(seconds * m_velocity);
	}

	void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_ship, states);
	}
}