#pragma once

#include <unordered_map>

#include <SFML-utils/ES.h>
#include <SFML-utils/Core.h>

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-book/server/Entity.h>
#include <SFML-book/server/Team.h>

class Game;

class CompAIMain : public sfutils::Component<CompAIMain, Entity>, public orm::SqlObject<CompAIMain>
{
public:
	CompAIMain();
	explicit CompAIMain(int gold, const sf::Time& timeDelta);
	CompAIMain& operator=(const CompAIMain& other);

	virtual void _afterLoad() override;
	virtual void _beforeSave() override;
	virtual void _beforeUpdate() override;

	orm::IntegerField _gold_amount;

	sf::Time _delta;
	orm::DoubleField _deltaAsDouble;

	sf::Time _elapsed;
	orm::DoubleField _elapsedAsDouble;

	ORM_MAKE_STATIC_COLUMN(_gold_amount, _deltaAsDouble, _elapsedAsDouble)
};

class CompAIWarrior : public sfutils::Component<CompAIWarrior, Entity>, public orm::SqlObject<CompAIWarrior>
{
public:
	CompAIWarrior();
	explicit CompAIWarrior(int hitPoint, const sf::Time& timeDelta, int range);
	CompAIWarrior& operator=(const CompAIWarrior& other);

	virtual void _afterLoad() override;
	virtual void _beforeSave() override;
	virtual void _beforeUpdate() override;

	orm::IntegerField _hitPoint;

	sf::Time _delta;
	orm::DoubleField _deltaAsDouble;

	sf::Time _elapsed;
	orm::DoubleField _elapsedAsDouble;

	orm::IntegerField _range;
	orm::UnsignedIntegerField _enemyId;

	ORM_MAKE_STATIC_COLUMN(_hitPoint, _deltaAsDouble, _elapsedAsDouble, _range, _enemyId)
};

class CompAIDefender : public sfutils::Component<CompAIDefender, Entity>, public orm::SqlObject<CompAIDefender>
{
public:
	CompAIDefender();
	explicit CompAIDefender(int hitPoint, const sf::Time& timeDelta, int range);
	CompAIDefender& operator=(const CompAIDefender& other);

	virtual void _afterLoad() override;
	virtual void _beforeSave() override;
	virtual void _beforeUpdate() override;

	orm::IntegerField _hitPoint;

	sf::Time _delta;
	orm::DoubleField _deltaAsDouble;

	sf::Time _elapsed;
	orm::DoubleField _elapsedAsDouble;

	orm::IntegerField _range;

	ORM_MAKE_STATIC_COLUMN(_hitPoint, _deltaAsDouble, _elapsedAsDouble, _range)
};

class CompAISpawner : public sfutils::Component<CompAISpawner, Entity>, public orm::SqlObject<CompAISpawner>
{
public:
	CompAISpawner();
	explicit CompAISpawner(book::MakeAs makeAs, int number, const sf::Time& timeDelta);
	CompAISpawner& operator=(const CompAISpawner& other);

	virtual void _afterLoad() override;
	virtual void _beforeSave() override;
	virtual void _beforeUpdate() override;

	book::MakeAs _makeAs;
	orm::IntegerField _makeAsTypeId;

	orm::IntegerField _number;

	sf::Time _delta;
	orm::DoubleField _deltaAsDouble;

	sf::Time _elapsed;
	orm::DoubleField _elapsedAsDouble;

	ORM_MAKE_STATIC_COLUMN(_makeAsTypeId, _number, _deltaAsDouble, _elapsedAsDouble)
};

class CompAIWalker : public sfutils::Component<CompAIWalker, Entity>, public orm::SqlObject<CompAIWalker>
{
public:
	CompAIWalker();
	explicit CompAIWalker(float speed);
	CompAIWalker& operator=(const CompAIWalker& other);

	virtual void _afterLoad() override;
	virtual void _beforeSave() override;
	virtual void _beforeUpdate() override;

	orm::FloatField _speed;

	sf::Vector2i _pathToTake;
	orm::IntegerField _pathToTakeX;
	orm::IntegerField _pathToTakeY;

	ORM_MAKE_STATIC_COLUMN(_speed, _pathToTakeX, _pathToTakeY)
};

class CompAIFlyer : public sfutils::Component<CompAIFlyer, Entity>, public orm::SqlObject<CompAIFlyer>
{
public:
	CompAIFlyer();
	explicit CompAIFlyer(float speed);
	CompAIFlyer& operator=(const CompAIFlyer& other);

	virtual void _afterLoad() override;
	virtual void _beforeSave() override;
	virtual void _beforeUpdate() override;

	orm::FloatField _speed;

	sf::Vector2i _pathToTake;
	orm::IntegerField _pathToTakeX;
	orm::IntegerField _pathToTakeY;

	ORM_MAKE_STATIC_COLUMN(_speed, _pathToTakeX, _pathToTakeY)
};

class CompTeam : public sfutils::Component<CompTeam, Entity>, public orm::SqlObject<CompTeam>
{
public:
	CompTeam();
	explicit CompTeam(Team::pointer team);
	CompTeam& operator=(const CompTeam& other);

	orm::FK<Team> _team;

	ORM_MAKE_STATIC_COLUMN(_team)
};

class CompSkin : public sfutils::Component<CompSkin, Entity>, public orm::SqlObject<CompSkin>
{
public:
	enum AnimationId : int
	{
		Stand = 0,
		Spawn,
		MoveLeft,
		MoveRight,
		HitLeft,
		HitRight
	};

	CompSkin();
	explicit CompSkin(short int animation);
	CompSkin& operator=(const CompSkin& other);

	orm::IntegerField _animationId;

	ORM_MAKE_STATIC_COLUMN(_animationId);
};

class CompHp : public sfutils::Component<CompHp, Entity>, public orm::SqlObject<CompHp>
{
public:
	CompHp();
	explicit CompHp(int hp);
	CompHp& operator=(const CompHp& other);

	orm::IntegerField _hp;
	orm::IntegerField _maxHp;

	ORM_MAKE_STATIC_COLUMN(_hp, _maxHp)
};