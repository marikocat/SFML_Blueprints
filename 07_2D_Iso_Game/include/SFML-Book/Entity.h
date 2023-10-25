#pragma once

#include "SFML-utils/ES.h"
#include "SFML-utils/Map.h"
#include "SFML-utils/Core.h"

namespace book
{
	class Level;
	class Entity : public sfutils::Entity<Entity>, public sf::Drawable
	{
	public:
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		Entity(sfutils::EntityManager<Entity>* manager, std::uint32_t id);

		sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f& pos);

		std::string name;

		using FuncType = std::function<void(Entity& self, const sf::Vector2i& myCoord, 
			Entity& enemi, const sf::Vector2i& enemyCoord, Level& level)>;

		FuncType onHit;
		FuncType onHitted;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}