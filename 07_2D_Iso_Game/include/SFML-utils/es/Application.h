#pragma once

#include "Entity.h"
#include "System.h"

namespace sfutils
{
    namespace es
    {
        template<typename ENTITY>
        class Application
        {
        public:
            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;

            Application();

            void update(sf::Time deltaTime);

            EntityManager<ENTITY> entities;
            SystemManager<ENTITY> systems;
        };
    }
}
#include "Application.tpl"