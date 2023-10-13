#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Configuration.h"

#include <memory>

namespace book
{
	class World : public sf::Drawable
	{
	public:
		World(const World&) = delete;
		World& operator=(const World&) = delete;

		World(int size_x, int size_y);
		~World();

		void update(sf::Time deltaTime);
		void updatePhysics(sf::Time deltaTime);

		Piece* newPiece();
		int clearLines(bool& del, const Piece& current);
		void updateGravity(int level);
		void add(Configuration::Sounds sound_id);
		bool isGameOver() const;
		void reset();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		b2World m_physicalWorld;
		void createWall(int pos_x, int pos_y, int size_x, int size_y);
		const int m_x;
		const int m_y;
		std::list<std::unique_ptr<sf::Sound>> m_sounds;
	};
}