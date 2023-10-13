#pragma once
#include "Widget.h"

namespace book
{
	namespace gui
	{
		class Label : public Widget
		{
		public:
			Label(const std::string& text, Widget* parent = nullptr);
			virtual ~Label();

			void setText(const std::string& text);
			void setCharacterSize(unsigned int size);
			unsigned int getCharacterSize() const;
			void setTextColor(const sf::Color& color);
			virtual sf::Vector2f getSize() const override;

		private:
			sf::Text m_text;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		};
	}
}