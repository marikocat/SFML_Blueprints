#include <SFML-utils/gui/Layout.h>
#include <SFML-utils/gui/ConfigurationGui.h>

namespace sfutils
{
	namespace gui
	{
		Layout::Layout(Widget* parent) : Widget(parent), _spacing(Configuration::Sizes::layout_spacing)
		{
		}

		Layout::~Layout()
		{
		}

		void Layout::setSpacing(float pixels)
		{
			if (pixels >= 0)
			{
				_spacing = pixels;
				updateShape();
			}
			else
				throw std::invalid_argument("pixel value must be >= 0");
		}
	}
}