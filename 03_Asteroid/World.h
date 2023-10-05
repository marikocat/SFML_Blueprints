#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <memory>
#include "Configuration.h"

namespace book
{
	class Entity;
	class World : public sf::Drawable
	{
	public:
		World(const World&) = delete;
		World& operator=(const World&) = delete;

		World(float x, float y);
		~World();
		
		void clear();

		void add(Entity* entity);
		void add(Configuration::Sounds sound_id);

		bool isCollide(const Entity& other);

		int size();
		int getX() const;
		int getY() const;
		const std::list<Entity*> getEntities() const;

		void update(sf::Time deltaTime);
	private:
		std::list<Entity*> m_entities;
		std::list<Entity*> m_entities_tmp;

		std::list<std::unique_ptr<sf::Sound>> m_sounds;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		const int m_x;
		const int m_y;
	};
}