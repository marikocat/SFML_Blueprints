#include "Layout.h"

#include <stdexcept>

namespace book
{
	namespace gui
	{
		Layout::Layout(Widget* parent) : Widget(parent), m_space(5) {}
		Layout::~Layout() {}

		void Layout::setSpace(float pixels)
		{
			if (pixels >= 0)
			{
				m_space = pixels;
				updateShape();
			}
			else
				throw std::invalid_argument("pixel value must be >= 0");
		}
	}
}