#pragma once

#include <SFML-utils/gui/Layout.h>

#include <vector>

namespace sfutils
{
	namespace gui
	{
		class HLayout : public Layout
		{
		public:
			HLayout(const HLayout&) = delete;
			HLayout& operator=(const HLayout&) = delete;

			HLayout(Widget* parent = nullptr);
			~HLayout();

			void add(Widget* widget);
			Widget* at(unsigned int index) const;

			virtual sf::Vector2f getSize() const override;

			virtual void clear() override;

		protected:
			virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) override;
			virtual void processEvents(const sf::Vector2f& parent_pos) override;

		private:
			std::vector<Widget*> _widgets;

			virtual void updateShape() override;

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		};
	}
}