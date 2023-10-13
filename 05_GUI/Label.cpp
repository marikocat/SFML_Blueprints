#include "Label.h"
#include "Configuration.h"

namespace book
{
	namespace gui
	{
		Label::Label(const std::string& text, Widget* parent) : Widget(parent)
		{
			m_text.setFont(Configuration::fonts.get(Configuration::Fonts::Gui));
			setText(text);
			setTextColor(sf::Color(180, 93, 23));
		}
		Label::~Label() {}

		void Label::setText(const std::string& text)
		{
			m_text.setString(text);
			updateShape();
		}

		void Label::setCharacterSize(unsigned int size)
		{
			m_text.setCharacterSize(size);
			updateShape();
		}

		unsigned int Label::getCharacterSize() const
		{
			return m_text.getCharacterSize();
		}

		void Label::setTextColor(const sf::Color& color)
		{
			m_text.setFillColor(color);
		}

		sf::Vector2f Label::getSize() const
		{
			sf::FloatRect rect = m_text.getGlobalBounds();
			return sf::Vector2f(rect.width, rect.height);
		}

		void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform.translate(m_position);
			target.draw(m_text, states);
		}
	}
}