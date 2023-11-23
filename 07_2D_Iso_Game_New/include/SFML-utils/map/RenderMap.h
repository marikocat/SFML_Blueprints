#pragma once

#include <SFML-utils/map/VMap.h>

namespace sfutils
{
	namespace map
	{
		class RenderMap
		{
		public:
			RenderMap(const RenderMap&) = delete;
			RenderMap& operator=(const RenderMap&) = delete;

			RenderMap(const VMap& map);

		protected:

		private:
			const VMap& _map;

		};
	}
}