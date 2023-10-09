#include "Board.h"

#include <cstring>
#include <cassert>

#define CELL_EMPTY -1

namespace book
{
	Board::Board(int columns, int lines, int cell_x, int cell_y) :
		m_columns(columns), m_lines(lines), m_cellX(cell_x), m_cellY(cell_y),
		m_isGameOver(false), m_gridContent(nullptr)
	{
		m_gridContent = new int[m_lines * m_columns];
		std::memset(m_gridContent, CELL_EMPTY, m_lines * m_columns * sizeof(int));

		sf::Color gridColor(55, 55, 55);
		m_grid = sf::VertexArray(sf::Lines, (m_lines + 1 + m_columns + 1) * 2);

		for (int i = 0; i <= m_lines; ++i)
		{
			m_grid[i * 2] = sf::Vertex(sf::Vector2f(0, i * m_cellY));
			m_grid[i * 2 + 1] = sf::Vertex(sf::Vector2f(m_columns * m_cellX, i * m_cellY));

			m_grid[i * 2].color = gridColor;
			m_grid[i * 2 + 1].color = gridColor;
		}

		for (int i = 0; i <= columns; ++i)
		{
			m_grid[(m_lines + 1) * 2 + i * 2] = sf::Vertex(sf::Vector2f(i * m_cellX, 0));
			m_grid[(m_lines + 1) * 2 + i * 2 + 1] = sf::Vertex(sf::Vector2f(i * m_cellX, m_lines * m_cellY));

			m_grid[(m_lines + 1) * 2 + i * 2].color = gridColor;
			m_grid[(m_lines + 1) * 2 + i * 2 + 1].color = gridColor;
		}
	}

	Board::~Board() { delete [] m_gridContent; }

	void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (int y = 0; y < m_lines; ++y)
			for (int x = 0; x < m_columns; ++x)
			{
				if (m_gridContent[y * m_columns + x] != CELL_EMPTY)
				{
					sf::RectangleShape rectangle(sf::Vector2f(m_cellX, m_cellY));
					rectangle.setFillColor(Piece::TetriminoColors[m_gridContent[y * m_columns + x]]);
					rectangle.setPosition(x * m_cellX, y * m_cellY);
					target.draw(rectangle, states);
				}
			}
		target.draw(m_grid, states);
	}

	void Board::spawn(Piece& piece)
	{
		piece.setPosition(m_columns / 2, 0);
		// add it in the grid
		clear(piece);
		for (int x = 0; x < m_columns; ++x)
			if (m_gridContent[x] != CELL_EMPTY)
			{
				m_isGameOver = true;
				break;
			}
		draw(piece);
	}

	bool Board::move(Piece& piece, int delta_x, int delta_y)
	{
		delta_x += piece.getPosX();
		delta_y += piece.getPosY();

		// delete the piece to not collide with itself
		clear(piece);

		// flood test
		bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = { {false} };
		bool movable = true;

		flood(delta_x, delta_y, (int)Piece::PIVOT_X, (int)Piece::PIVOT_Y,
			piece.getType(), piece.getRotation(), visited, movable);

		if (movable)
			piece.setPosition(delta_x, delta_y);
		draw(piece);

		return movable;
	}

	bool Board::isFallen(const Piece& piece)
	{
		clear(piece);

		bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = { {false} };
		bool fallen = true;

		flood(piece.getPosX(), 
			piece.getPosY() + 1,
			(int)Piece::PIVOT_X,
			(int)Piece::PIVOT_Y,
			piece.getType(), piece.getRotation(),
			visited, fallen);

		// add it to the grid
		draw(piece);

		return fallen;
	}

	void Board::drop(Piece& piece) 
	{ 
		while (move(piece, 0, 1));
	}

	bool Board::rotateLeft(Piece& piece)
	{
		int rotation = piece.getRotation();
		if (rotation > 0)
			--rotation;
		else
			rotation = Piece::NB_ROTATIONS - 1;
		return rotate(piece, rotation);
	}

	bool Board::rotateRight(Piece& piece)
	{
		int rotation = piece.getRotation();
		if (rotation < Piece::NB_ROTATIONS - 1)
			++rotation;
		else
			rotation = 0;
		return rotate(piece, rotation);
	}

	bool Board::isGameOver() { return m_isGameOver; }

	bool Board::rotate(Piece& piece, int rotation)
	{
		assert(rotation >= 0 and rotation < Piece::NB_ROTATIONS);

		clear(piece);

		bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = { {false} };
		bool rotable = true;

		flood((int)piece.getPosX(), 
			(int)piece.getPosY(),
			(int)Piece::PIVOT_X, 
			(int)Piece::PIVOT_Y,
			piece.getType(), 
			rotation,
			visited, 
			rotable);

		if (rotable)
			piece.setRotation(rotation);
		draw(piece);

		return rotable;
	}

	void Board::draw(const Piece& piece)
	{
		flood(piece, piece.getType());
	}

	void Board::clear(const Piece& piece)
	{
		flood(piece, CELL_EMPTY);
	}

	void Board::flood(const Piece& piece, int value)
	{
		bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = { {false} };

		flood((int)piece.getPosX(),
			(int)piece.getPosY(),
			(int)Piece::PIVOT_X,
			(int)Piece::PIVOT_Y,
			piece.getType(),
			piece.getRotation(),
			visited, 
			value);
	}

	void Board::flood(int grid_x, int grid_y, int piece_x, int piece_y,
		Piece::TetriminoTypes type, int rotation, bool visited[][Piece::MATRIX_SIZE], int value)
	{
		// limit tests
		if (piece_x < 0 or piece_x >= Piece::MATRIX_SIZE
			or piece_y < 0 or piece_y >= Piece::MATRIX_SIZE
			or grid_x < 0 or grid_x >= (int)m_columns
			or grid_y < 0 or grid_y >= (int)m_lines
			or visited[piece_y][piece_x] == true
			or Piece::TetriminoPieces[type][rotation][piece_y][piece_x] == 0)
			return;

		visited[piece_y][piece_x] = true;

		// add the value to the grid
		m_gridContent[grid_y * m_columns + grid_x] = value;

		//recursiv call for each square around : 4 directions
		flood(grid_x, grid_y - 1, piece_x, piece_y - 1, type, rotation, visited, value);
		flood(grid_x + 1, grid_y, piece_x + 1, piece_y, type, rotation, visited, value);
		flood(grid_x, grid_y + 1, piece_x, piece_y + 1, type, rotation, visited, value);
		flood(grid_x - 1, grid_y, piece_x - 1, piece_y, type, rotation, visited, value);
	}

	void Board::flood(int grid_x, int grid_y, int piece_x, int piece_y,
		Piece::TetriminoTypes type, int rotation, bool visited[][Piece::MATRIX_SIZE], bool& flag)
	{
		// limit tests
		if (piece_x < 0 or piece_x >= Piece::MATRIX_SIZE
			or piece_y < 0 or piece_y >= Piece::MATRIX_SIZE
			or visited[piece_y][piece_x] == true
			or Piece::TetriminoPieces[type][rotation][piece_y][piece_x] == 0)
			return;

		visited[piece_y][piece_x] = true;

		// collision tests
		if (grid_x < 0 or grid_x >= (int)m_columns
			or grid_y < 0 or grid_y >= (int)m_lines
			or m_gridContent[grid_y * m_columns + grid_x] != CELL_EMPTY)
		{
			flag = false;
			return;
		}

		//recursiv call for each square around : 4 directions
		flood(grid_x, grid_y - 1, piece_x, piece_y - 1, type, rotation, visited, flag);
		flood(grid_x + 1, grid_y, piece_x + 1, piece_y, type, rotation, visited, flag);
		flood(grid_x, grid_y + 1, piece_x, piece_y + 1, type, rotation, visited, flag);
		flood(grid_x - 1, grid_y, piece_x - 1, piece_y, type, rotation, visited, flag);
	}

	void Board::clearLine(int yy)
	{
		assert(yy < m_lines);
		for (int y = yy; y > 0; --y)
			for (int x = 0; x < m_columns; ++x)
				m_gridContent[y * m_columns + x] = m_gridContent[(y - 1) * m_columns + x];
	}

	int Board::clearLines(const Piece& piece)
	{
		int nb_delete = 0;
		clear(piece);
		for (int y = 0; y < m_lines; ++y)
		{
			int x = 0;
			for (; m_gridContent[y * m_columns + x] != CELL_EMPTY and x < m_columns; ++x);
			if (x == m_columns)
			{
				clearLine(y);
				++nb_delete;
			}
		}
		draw(piece);
		return nb_delete;
	}
}

// mine