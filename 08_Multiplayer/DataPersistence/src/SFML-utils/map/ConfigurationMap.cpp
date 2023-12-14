#include <SFML-utils/map/ConfigurationMap.h>

namespace sfutils
{
	namespace map
	{
		ActionMap<int> Configuration::defaultMapInputs;
		Configuration::__Initializer Configuration::__initializer__;

		void Configuration::initEvents()
		{
			defaultMapInputs.map(MapInputs::MoveUp, Action(sf::Keyboard::Up));
			defaultMapInputs.map(MapInputs::MoveDown, Action(sf::Keyboard::Down));
			defaultMapInputs.map(MapInputs::MoveLeft, Action(sf::Keyboard::Left));
			defaultMapInputs.map(MapInputs::MoveRight, Action(sf::Keyboard::Right));
		}

		void Configuration::init()
		{
			initEvents();
		}
	}
}