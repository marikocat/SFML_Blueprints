#include "Piece.h"
#include <cassert>

namespace book
{
	const sf::Color Piece::TetriminoColors[Piece::TetriminoTypes::SIZE] = {
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Cyan,
		sf::Color::Magenta,
		sf::Color::White,
		sf::Color(195,132,58)
	};

    const char Piece::TetriminoPieces[Piece::TetriminoTypes::SIZE][Piece::NB_ROTATIONS][Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {
        { // O
            {
                {0,0,0,0},
                {0,1,2,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,2,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,2,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,2,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        },
        {//I
            {
                {0,0,0,0},
                {1,1,2,1},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,2,0},
                {0,0,1,0},
                {0,0,1,0}
            },
            {
                {0,0,0,0},
                {1,1,2,1},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,2,0},
                {0,0,1,0},
                {0,0,1,0}
            }
        },
        {//S
            {
                {0,0,0,0},
                {0,0,2,1},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,2,1},
                {0,0,0,1},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,0,2,1},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,2,1},
                {0,0,0,1},
                {0,0,0,0}
            }
        },
        {//Z
            {
                {0,0,0,0},
                {0,1,2,0},
                {0,0,1,1},
                {0,0,0,0}
            },
            {
                {0,0,0,1},
                {0,0,2,1},
                {0,0,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,2,0},
                {0,0,1,1},
                {0,0,0,0}
            },
            {
                {0,0,0,1},
                {0,0,2,1},
                {0,0,1,0},
                {0,0,0,0}
            }
        },
        {//L
            {
                {0,0,0,0},
                {0,1,2,1},
                {0,1,0,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,2,0},
                {0,0,1,1},
                {0,0,0,0}
            },
            {
                {0,0,0,1},
                {0,1,2,1},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,1,1,0},
                {0,0,2,0},
                {0,0,1,0},
                {0,0,0,0}
            }
        },
        {//J
            {
                {0,0,0,0},
                {0,1,2,1},
                {0,0,0,1},
                {0,0,0,0}
            },
            {
                {0,0,1,1},
                {0,0,2,0},
                {0,0,1,0},
                {0,0,0,0}
            },
            {
                {0,1,0,0},
                {0,1,2,1},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,2,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        },
        {//T
            {
                {0,0,0,0},
                {0,1,2,1},
                {0,0,1,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,2,1},
                {0,0,1,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,1,2,1},
                {0,0,0,0},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,1,2,0},
                {0,0,1,0},
                {0,0,0,0}
            }
        }
    };

    Piece::Piece(TetriminoTypes type, short int rotation) :
        m_type(type), m_rotation(rotation), m_positionX(0), m_positionY(0)
    {
        assert(rotation >= 0 and rotation < NB_ROTATIONS); // macro that will raise an error and exit the program if the expression such as parameter is false
    }

    Piece::TetriminoTypes Piece::getType() const { return m_type; }

    void Piece::setRotation(short int rotation)
    {
        assert(rotation >= 0 and rotation < NB_ROTATIONS);
        m_rotation = rotation;
        m_clockSinceLastMove.restart();
    }

    short int Piece::getRotation() const { return m_rotation; }

    void Piece::setPosition(int x, int y)
    {
        m_positionX = x;
        m_positionY = y;
        m_clockSinceLastMove.restart();
    }

    int Piece::getPosX() const { return m_positionX; }
    int Piece::getPosY() const { return m_positionY; }

    sf::Time Piece::getTimeSinceLastMove()const
    {
        return m_clockSinceLastMove.getElapsedTime();
    }
}