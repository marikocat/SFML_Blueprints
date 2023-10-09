#pragma once
#include <SFML/Graphics.hpp>

namespace book
{
	class Stats : public sf::Transformable, public sf::Drawable
	{
	public:
		Stats();
		void addLines(int lines);
		unsigned int getLvl() const;
		void gameOver();
	private:
		virtual void draw(sf::RenderTarget& target,
			sf::RenderStates states = sf::RenderStates::Default)
			const override;

		unsigned int m_nbRows;
		unsigned int m_nbScore;
		unsigned int m_nbLvl;
		bool m_isGameOver;

		sf::Text m_textRows;
		sf::Text m_textScore;
		sf::Text m_textLvl;
		sf::Text m_textGameOver;

		sf::Text m_textInformation;

		sf::Font m_font;
	};
}