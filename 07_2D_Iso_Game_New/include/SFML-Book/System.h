#pragma once

#include <SFML-utils/ES.h>

#include <SFML-Book/Entity.h>

namespace book
{
	class Level;

	struct SysAIMain : sfutils::System<SysAIMain, Entity>
	{
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
	};

	struct SysAIWarrior : sfutils::System<SysAIWarrior, Entity>
	{
		explicit SysAIWarrior(Level& level);

		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;

		Level& _level;
	};

	struct SysAIDefender : sfutils::System<SysAIDefender, Entity>
	{
		explicit SysAIDefender(Level& level);

		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;

		Level& _level;
	};

	struct SysAISpawner : sfutils::System<SysAISpawner, Entity>
	{
		explicit SysAISpawner(Level& level);

		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;

		Level& _level;
	};

	struct SysAIWalker : sfutils::System<SysAIWalker, Entity>
	{
		explicit SysAIWalker(Level& level);

		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;

		Level& _level;
	};

	struct SysAIFlyer : sfutils::System<SysAIFlyer, Entity>
	{
		explicit SysAIFlyer(Level& level);

		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;

		Level& _level;
	};

	struct SysSkin : sfutils::System<SysSkin, Entity>
	{
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
	};

	struct SysHp : sfutils::System<SysHp, Entity>
	{
		explicit SysHp(Level& level);

		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;

		Level& _level;
	};

	struct SysEffect : sfutils::System<SysEffect, Entity>
	{
		explicit SysEffect(Level& level);

		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;

		Level& _level;
	};
}