#include "Stats.h"
#include "Configuration.h"

#define FONtSIZE   24

namespace book
{

    Stats::Stats() : m_nbRows(0), m_nbScore(0), m_nbLvl(0), m_isGameOver(false)
    {
        m_textRows.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
        m_textRows.setString("rows : 0");
        m_textRows.setCharacterSize(FONtSIZE);
        m_textRows.setPosition(0, 0);

        m_textScore.setFont(Configuration::fonts.get(Configuration::Gui));
        m_textScore.setString("score : 0");
        m_textScore.setCharacterSize(FONtSIZE);
        m_textScore.setPosition(0, FONtSIZE + 1);

        m_textLvl.setFont(Configuration::fonts.get(Configuration::Gui));
        m_textLvl.setString("lvl : 0");
        m_textLvl.setCharacterSize(FONtSIZE);
        m_textLvl.setPosition(0, (FONtSIZE + 1) * 2);

        m_textGameOver.setFont(Configuration::fonts.get(Configuration::Gui));
        m_textGameOver.setString("Game Over");
        m_textGameOver.setCharacterSize(72);
        m_textGameOver.setPosition(0, 0);
    }

    bool Stats::isGameOver()const
    {
        return m_isGameOver;
    }

    void Stats::setGameOver(bool g)
    {
        m_isGameOver = g;
    }

    int Stats::getLevel()const
    {
        return m_nbLvl;
    }

    void Stats::addLines(int lines)
    {
        if (lines > 0)
        {
            //update number of lines
            m_nbRows += lines;
            m_textRows.setString("rows : " + std::to_string(m_nbRows));

            //update the score
            switch (lines)
            {
            case 1: m_nbScore += 40 * (m_nbLvl + 1); break;
            case 2: m_nbScore += 100 * (m_nbLvl + 1); break;
            case 3: m_nbScore += 300 * (m_nbLvl + 1); break;
            default: m_nbScore += 1200 * (m_nbLvl + 1); break;
            }

            m_textScore.setString("score : " + std::to_string(m_nbScore));

            m_nbLvl = m_nbRows / 10;

            //update the lvl
            m_textLvl.setString("lvl : " + std::to_string(m_nbLvl));
        }
    }

    unsigned int Stats::getLvl()const
    {
        return m_nbLvl;
    }

    void Stats::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (not m_isGameOver)
        {
            //make states
            states.transform *= getTransform();

            //draw
            target.draw(m_textRows, states);
            target.draw(m_textScore, states);
            target.draw(m_textLvl, states);
        }
        else
            target.draw(m_textGameOver, states);
    }

}