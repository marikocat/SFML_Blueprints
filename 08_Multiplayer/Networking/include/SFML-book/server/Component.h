#pragma once

#include <SFML-utils/ES.h>
#include <SFML-utils/Core.h>

#include <unordered_map>

#include <SFML-book/server/Entity.h>

namespace book
{
	class Team;
	class Game;

	// add some gold periodically
	struct CompAIMain : sfutils::Component<CompAIMain, Entity>
	{
		explicit CompAIMain(int gold, const sf::Time& timeDelta);

		const int _gold_amount;
		const sf::Time _delta;
		sf::Time _elapsed;
	};

	struct CompAIWarrior : sfutils::Component<CompAIWarrior, Entity>
	{
		explicit CompAIWarrior(int hitPoint, const sf::Time& timeDelta, int range);

		const int _hitPoint;
		const sf::Time _delta;
		sf::Time _elapsed;
		const int _range;
		std::uint32_t _enemyId;
	};

	struct CompAIDefender : sfutils::Component<CompAIDefender, Entity>
	{
		explicit CompAIDefender(int hitPoint, const sf::Time& timeDelta, int range);

		const int _hitPoint;
		const sf::Time _delta;
		sf::Time _elapsed;
		const int _range;
	};

	struct CompAISpawner : sfutils::Component<CompAISpawner, Entity>
	{
		using FuncType = std::function<void(Entity& entity, Team* team, Game& game)>;

		explicit CompAISpawner(FuncType makeAs, int number, const sf::Time& timeDelta);

		FuncType _makeAs;
		const int _number;
		const sf::Time _delta;
		sf::Time _elapsed;
	};

	struct CompAIWalker : sfutils::Component<CompAIWalker, Entity>
	{
		explicit CompAIWalker(float speed);

		const float _speed;
		sf::Vector2i _pathToTake;
	};

	struct CompAIFlyer : sfutils::Component<CompAIFlyer, Entity>
	{
		explicit CompAIFlyer(float speed);

		const float _speed;
		sf::Vector2i _pathToTake;
	};

	struct CompTeam : sfutils::Component<CompTeam, Entity>
	{
		explicit CompTeam(Team* team);

		Team* _team;
	};

	struct CompSkin : sfutils::Component<CompSkin, Entity>
	{
		enum AnimationId : int
		{
			Stand = 0,
			Spawn,
			MoveLeft,
			MoveRight,
			HitLeft,
			HitRight
		};

		explicit CompSkin(short int animation);

		short int _animationId;
	};

	struct CompHp : sfutils::Component<CompHp, Entity>
	{
		explicit CompHp(int hp);

		int _hp;
		const int _maxHp;
	};

	struct CompUpgradable : sfutils::Component<CompUpgradable, Entity>
	{
	};
}