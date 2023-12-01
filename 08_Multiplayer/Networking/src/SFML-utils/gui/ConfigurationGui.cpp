#include <SFML-utils/gui/ConfigurationGui.h>

namespace sfutils
{
	namespace gui
	{
		ResourceManager<sf::Font, int> Configuration::default_fonts;
		ActionMap<int> Configuration::default_gui_inputs;
		Configuration::__Initializer Configuration::__initializer__;

		sf::Color Configuration::Colors::button_fill(86, 20, 19);
		sf::Color Configuration::Colors::button_outline(146, 20, 19);
		sf::Color Configuration::Colors::label_text(180, 93, 23);
		float Configuration::Colors::lighting = 1.4;

		unsigned int Configuration::Sizes::button_outline_thickness = 5;
		unsigned int Configuration::Sizes::layout_spacing = 10;

		void Configuration::initFont()
		{
			default_fonts.load(Fonts::Gui, "media/font/default.ttf");
		}

		void Configuration::initEvents()
		{
			default_gui_inputs.map(GuiInputs::Escape, Action(sf::Keyboard::Key::Escape, sfutils::Action::Type::Pressed));
		}

		void Configuration::init()
		{
			initFont();
			initEvents();
		}
	}
}