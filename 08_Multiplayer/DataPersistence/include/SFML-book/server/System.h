#pragma once

#include <SFML-utils/ES.h>

#include <SFML-book/server/Entity.h>

class Game;

namespace book
{
	struct SysAIMain : sfutils::System<SysAIMain, Entity>
	{
		explicit SysAIMain(Game& game);
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
		Game& _game;
	};

	struct SysAIWarrior : sfutils::System<SysAIWarrior, Entity>
	{
		explicit SysAIWarrior(Game& game);
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
		Game& _game;
	};

	struct SysAIDefender : sfutils::System<SysAIDefender, Entity>
	{
		explicit SysAIDefender(Game& game);
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
		Game& _game;
	};

	struct SysAISpawner : sfutils::System<SysAISpawner, Entity>
	{
		explicit SysAISpawner(Game& game);
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
		Game& _game;
	};

	struct SysAIWalker : sfutils::System<SysAIWalker, Entity>
	{
		explicit SysAIWalker(Game& game);
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
		Game& _game;
	};

	struct SysAIFlyer : sfutils::System<SysAIFlyer, Entity>
	{
		explicit SysAIFlyer(Game& game);
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
		Game& _game;
	};

	struct SysHp : sfutils::System<SysHp, Entity>
	{
		explicit SysHp(Game& game);
		virtual void update(sfutils::EntityManager<Entity>& manager, const sf::Time& dt) override;
		Game& _game;
	};
}