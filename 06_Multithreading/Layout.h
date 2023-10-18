#pragma once
#include <SFML/Graphics.hpp>

#include "Widget.h"

namespace book
{
	namespace gui
	{
        class Layout : protected Widget
        {
        public:
            Layout(const Layout&) = delete;
            Layout& operator=(const Layout&) = delete;

            Layout(Widget* parent = nullptr);
            virtual ~Layout();

            void setSpace(float pixels);

        protected:
            friend class Container;

            float m_space;
        };
	}
}