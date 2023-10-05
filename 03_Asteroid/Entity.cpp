#include "Entity.h"

namespace book
{
	Entity::Entity(Configuration::Textures tex_id, World& world) :
		m_world(world), m_alive(true)
	{
		sf::Texture& texture = Configuration::textures.get(tex_id);
		m_sprite.setTexture(texture);
		m_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	}

	Entity::~Entity()
	{
	}

	const sf::Vector2f& Entity::getPosition() const
	{
		return m_sprite.getPosition();
	}

	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite, states);
	}

	bool Entity::isAlive() const { return m_alive; }
	void Entity::onDestroy() { m_alive = false; }
}