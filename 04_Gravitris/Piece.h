#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

namespace book
{
	constexpr int BOOK_BOX_SIZE = 32;
	constexpr int BOOK_BOX_SIZE_2 = BOOK_BOX_SIZE / 2;

	class Piece : public sf::Drawable
	{
	public:
		Piece(const Piece&) = delete;
		Piece& operator=(const Piece&) = delete;

		enum TetriminoTypes {O = 0, I, S, Z, L, J, T, SIZE};
		static const sf::Color TetriminoColors[TetriminoTypes::SIZE];

		Piece(b2World& world, int pos_x, int pos_y, TetriminoTypes type, float rotation);
		~Piece();

		void update();
		void rotate(float angle);
		void moveX(int direction);
		b2Body* getBody() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		b2Fixture* createPart(int pos_x, int pos_y, TetriminoTypes type);
		///< position is relative to the piece int the matrix coordinate (0 to 3)

		b2Body* m_body;
		b2World& m_world;
	};
}
