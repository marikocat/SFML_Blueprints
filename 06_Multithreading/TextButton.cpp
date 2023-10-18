#include "TextButton.h"
#include "Button.h"

namespace book
{
	namespace gui
	{
		TextButton::TextButton(const std::string& text, Widget* parent) : Button(parent), m_label(text, this)
		{
			setFillColor(sf::Color(86, 20, 19));
			setOutlineThikness(5);
			setOutlineColor(sf::Color(146, 20, 19));
		}
		TextButton::~TextButton() {}

		void TextButton::setText(const std::string& text)
		{
			m_label.setText(text);
		}

		void TextButton::setCharacterSize(unsigned int size)
		{
			m_label.setCharacterSize(size);
		}

		void TextButton::setTextColor(const sf::Color& color)
		{
			m_label.setTextColor(color);
		}

		void TextButton::setFillColor(const sf::Color& color)
		{
			m_fillColor = color;
			m_shape.setFillColor(m_fillColor);
		}

		void TextButton::setOutlineColor(const sf::Color& color)
		{
			m_outlineColor = color;
			m_shape.setOutlineColor(m_outlineColor);
		}

		void TextButton::setOutlineThikness(float thickness)
		{
			m_shape.setOutlineThickness(thickness);
		}

		sf::Vector2f TextButton::getSize() const
		{
			sf::FloatRect rect = m_shape.getGlobalBounds();
			return sf::Vector2f(rect.width, rect.height);
		}

		void TextButton::updateShape()
		{
			sf::Vector2f label_size = m_label.getSize();
			unsigned int char_size = m_label.getCharacterSize();
			m_shape.setSize(sf::Vector2f(char_size * 2 + label_size.x,
				char_size * 2 + label_size.y));
			m_label.setPosition(char_size, char_size);
			Widget::updateShape();
		}

		void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform.translate(m_position);
			target.draw(m_shape, states);
			target.draw(m_label, states);
		}

		void TextButton::onMouseEntered()
		{
			const float light = 1.4f;
			m_shape.setOutlineColor(sf::Color(m_outlineColor.r * light, m_outlineColor.g * light, m_outlineColor.b * light));
			m_shape.setFillColor(sf::Color(m_fillColor.r * light, m_fillColor.g * light, m_fillColor.b * light));
		}

		void TextButton::onMouseLeft()
		{
			m_shape.setOutlineColor(m_outlineColor);
			m_shape.setFillColor(m_fillColor);
		}
	}
}