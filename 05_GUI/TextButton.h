#pragma once
#include "Button.h"
#include "Label.h"

namespace book
{
	namespace gui
	{
		class TextButton : public Button
		{
		public:
			TextButton(const std::string& text, Widget* parent = nullptr);
			virtual ~TextButton();

			void setText(const std::string& text);
			void setCharacterSize(unsigned int size);

			void setTextColor(const sf::Color& color);
			void setFillColor(const sf::Color& color);
			void setOutlineColor(const sf::Color& color);
			void setOutlineThikness(float thickness);
			virtual sf::Vector2f getSize() const override;

		private:
			sf::RectangleShape m_shape;
			Label m_label;
			void updateShape() override;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			sf::Color m_fillColor;
			sf::Color m_outlineColor;
			virtual void onMouseEntered() override;
			virtual void onMouseLeft() override;
		};
	}
}