#pragma once

#include <SFML-utils/ES.h>

#include <SFML-book/client/Entity.h>

namespace book
{
	class Level;

	struct SysSkin : sfutils::System<SysSkin, Entity>
	{
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
	};

	struct SysHp : sfutils::System<SysHp, Entity>
	{
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
	};
}