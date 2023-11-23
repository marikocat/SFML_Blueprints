#pragma once

#include <SFML/Graphics.hpp>

#include <SFML-utils/gui/Widget.h>

namespace sfutils
{
	namespace gui
	{
		class Layout : virtual protected Widget
		{
		public:
			Layout(const Layout&) = delete;
			Layout& operator=(const Layout&) = delete;

			Layout(Widget* parent = nullptr);
			virtual ~Layout();

			virtual void clear() = 0;

			void setSpacing(float pixels);

		protected:
			friend class Container;
			friend class Frame;

			float _spacing;

		};
	}
}