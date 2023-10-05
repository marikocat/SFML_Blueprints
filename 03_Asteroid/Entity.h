#pragma once
#include <SFML/Graphics.hpp>
#include "Configuration.h"

namespace book
{
	class World;
	class Entity : public sf::Drawable
	{
	public:
		// Constructors
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		Entity(Configuration::Textures tex_id, World& world);
		virtual ~Entity();

		// Helpers
		virtual bool isAlive() const;

		const sf::Vector2f& getPosition() const;
		template<typename ... Args>
		void setPosition(Args&& ... args);

		virtual bool isCollide(const Entity& other) const = 0;

		// Updates
		virtual void update(sf::Time deltaTime) = 0;
		virtual void onDestroy();

	protected:
		friend class Meteor;
		friend class Player;
		friend class Saucer;
		friend class ShootPlayer;
		friend class ShootSaucer;
		sf::Sprite m_sprite;
		sf::Vector2f m_impulse;
		World& m_world;
		bool m_alive;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
#include "Entity.tpl"