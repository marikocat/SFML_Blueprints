#include "Stats.h"

#define FONT_SIZE 24

namespace book
{
	Stats::Stats() : m_nbRows(0), m_nbScore(0), m_nbLvl(0),
		m_isGameOver(false)
	{
		m_font.loadFromFile("media/fonts/trs-million.ttf");

		m_textRows.setFont(m_font);
		m_textRows.setString("rows : 0");
		m_textRows.setCharacterSize(FONT_SIZE);
		m_textRows.setPosition(0, 0);

		m_textScore.setFont(m_font);
		m_textScore.setString("score : 0");
		m_textScore.setCharacterSize(FONT_SIZE);
		m_textScore.setPosition(0, FONT_SIZE + 1);

		m_textLvl.setFont(m_font);
		m_textLvl.setString("lvl : 0");
		m_textLvl.setCharacterSize(FONT_SIZE);
		m_textLvl.setPosition(0, (FONT_SIZE + 1) * 2);

		m_textInformation.setFont(m_font);
		m_textInformation.setString("Use arrow keys to move\n\tS and D to rotate");
		m_textInformation.setFillColor(sf::Color(0, 255, 0));
		m_textInformation.setCharacterSize(FONT_SIZE);
		m_textInformation.setPosition(0, (FONT_SIZE + 1) * 4);

		m_textGameOver.setFont(m_font);
		m_textGameOver.setString("Game Over");
		m_textGameOver.setCharacterSize(72);
		m_textGameOver.setPosition(0, 0);
	}

	void Stats::gameOver() { m_isGameOver = true; }

	void Stats::addLines(int lines)
	{
		if (lines > 0)
		{
			m_nbRows += lines;
			m_textRows.setString("rows : " + std::to_string(m_nbRows));
			m_textScore.setString("score : " + std::to_string(m_nbScore));
			switch (lines)
			{
			case 1: m_nbScore += 40 * (m_nbLvl + 1); break;
			case 2: m_nbScore += 100 * (m_nbLvl + 1); break;
			case 3: m_nbScore += 300 * (m_nbLvl + 1); break;
			case 4: m_nbScore += 1200 * (m_nbLvl + 1); break;
			default: break;
			}
			m_nbLvl = m_nbRows / 10;
			m_textLvl.setString("lvl : " + std::to_string(m_nbLvl));
		}
	}

	unsigned int Stats::getLvl() const { return m_nbLvl; }
	void Stats::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (not m_isGameOver)
		{
			states.transform *= getTransform();

			target.draw(m_textRows, states);
			target.draw(m_textScore, states);
			target.draw(m_textLvl, states);
			target.draw(m_textInformation, states);
		}
		else
			target.draw(m_textGameOver, states);
	}
}