#pragma once
#include <SFML/Graphics.hpp>

namespace book
{
	class Board;

	class Piece
	{
	public:
		static const unsigned short int NB_ROTATIONS = 4; // number of rotations
		static const unsigned short int MATRIX_SIZE = 4;
		static const unsigned int PIVOT_Y = 1;
		static const unsigned int PIVOT_X = 2;

		enum TetriminoTypes {O = 0, I, S, Z, L, J, T, SIZE}; // diffrent kind of pieces
		static const sf::Color TetriminoColors[TetriminoTypes::SIZE];
		// different colors for each kind of piece
		static const char TetriminoPieces[TetriminoTypes::SIZE][NB_ROTATIONS][MATRIX_SIZE][MATRIX_SIZE];
		// store all the different shapes

		Piece(const Piece&) = delete;
		Piece& operator=(const Piece&) = delete;

		Piece(TetriminoTypes type, short int rotation);

		TetriminoTypes getType() const;
		void setRotation(short int rotation); // set the rotation
		short int getRotation() const;
		void setPosition(int x, int y); // set the position in the board

		int getPosX() const;
		int getPosY() const;
		sf::Time getTimeSinceLastMove() const;

	private:
		const TetriminoTypes m_type; // the piece type
		short int m_rotation; // the piece rotation
		int m_positionX; // position in the board
		int m_positionY; // position in the board
		sf::Clock m_clockSinceLastMove;
	};
}