#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"

namespace book
{
	class Board : public sf::Transformable, public sf::Drawable
	{
	public:
		//Make the class non copyable
		Board(const Board&) = delete;
		Board& operator=(const Board&) = delete;

		static const int DEFAULT_BOARD_COLUMNS = 10;
		static const int DEFAULT_BOARD_LINES = 20;
		static const int DEFAULT_CELL_X = 24;
		static const int DEFAULT_CELL_Y = 24;

		Board(int columns = DEFAULT_BOARD_COLUMNS, int lines = DEFAULT_BOARD_LINES,
			int cell_x = DEFAULT_CELL_X, int cell_y = DEFAULT_CELL_Y);
		~Board();

		void spawn(Piece& piece);
		bool move(Piece& piece, int delta_x, int delta_y);
		bool isFallen(const Piece& piece);
		void drop(Piece& piece);
		bool rotateLeft(Piece& piece);
		bool rotateRight(Piece& piece);
		bool isGameOver();
		int clearLines(const Piece& piece); // clear all possible lines

	private:
		bool rotate(Piece& piece, int rotation);

		void draw(const Piece& piece);
		void clear(const Piece& piece);

		virtual void draw(sf::RenderTarget& target, 
			sf::RenderStates states = sf::RenderStates::Default) const override;

		void flood(const Piece& piece, int value);
		void flood(int grid_x, int grid_y,
			int piece_x, int piece_y,
			Piece::TetriminoTypes type, int rotation,
			bool visited[][Piece::MATRIX_SIZE], int value);
		void flood(int grid_x, int grid_y,
			int piece_x, int piece_y,
			Piece::TetriminoTypes type, int rotation,
			bool visited[][Piece::MATRIX_SIZE], bool& flag);

		void clearLine(int y);

		const int m_columns;
		const int m_lines;
		const int m_cellX;
		const int m_cellY;

		bool m_isGameOver;

		sf::VertexArray m_grid; // grid borders
		int* m_gridContent; // lines * columns
	};
}