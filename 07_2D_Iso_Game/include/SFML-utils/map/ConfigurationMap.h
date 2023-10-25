#pragma once

#include "SFML-utils/core/ActionMap.h"

#include <SFML/Graphics.hpp>

namespace sfutils
{
	namespace map
	{
		class Configuration
		{
		public:
			Configuration() = delete;
			Configuration(const Configuration&) = delete;
			Configuration& operator=(const Configuration&) = delete;

			enum MapInputs
			{
				MoveUp,
				MoveDown,
				MoveLeft,
				MoveRight
			};

			static ActionMap<int> defaultMapInputs;

		private:
			static void initEvents();

			static void init();

			static struct __Initializer
			{
				__Initializer()
				{
					Configuration::init();
				}
			} __initializer__;
		};
	}
}