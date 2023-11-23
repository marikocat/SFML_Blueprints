#pragma once

#include <SFML-utils/gui/Button.h>
#include <SFML-utils/gui/Sprite.h>

namespace sfutils
{
	namespace gui
	{
		class SpriteButton : virtual public Widget, public Button, public Sprite
		{
		public:
			SpriteButton(const SpriteButton&) = delete;
			SpriteButton& operator=(const SpriteButton&) = delete;

			SpriteButton(const sf::Texture& tex, Widget* parent = nullptr);
			~SpriteButton();

			void setColor(const sf::Color& color) override;

		private:
			sf::Color _color;

			virtual void onMouseEntered() override;
			virtual void onMouseLeft() override;

			void updateShape() override;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		};
	}
}