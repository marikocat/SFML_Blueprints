#pragma once
#include <SFML/Graphics.hpp>

namespace book
{
    class Stats : public sf::Transformable, public sf::Drawable
    {
    public:
        Stats();

        void addLines(int lines);
        unsigned int getLvl()const;

        bool isGameOver()const;
        void setGameOver(bool);

        int getLevel()const;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override; //< draw override from Drawable

        unsigned int m_nbRows;
        unsigned int m_nbScore;
        unsigned int m_nbLvl;

        bool m_isGameOver;

        sf::Text m_textRows;
        sf::Text m_textScore;
        sf::Text m_textLvl;
        sf::Text m_textGameOver;
    };
}