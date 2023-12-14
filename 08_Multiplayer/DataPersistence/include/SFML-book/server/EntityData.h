#pragma once

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-book/server/Component.h>
#include <SFML-book/server/Game.h>

class Entity;

class EntityData : public orm::SqlObject<EntityData>
{
public:
	EntityData();

	static EntityData::pointer createFromEntity(Entity& entity, Game::pointer game);

	std::uint32_t convertToEntity(Game& game);

	orm::FK<Game> _game;
	orm::FloatField _coordX;
	orm::FloatField _coordY;
	orm::IntegerField _type;

	orm::FK<CompAIMain> _AIMain;
	orm::FK<CompAIWarrior> _AIWarrior;
	orm::FK<CompAIDefender> _AIDefender;
	orm::FK<CompAISpawner> _AISpawner;
	orm::FK<CompAIWalker> _AIWalker;
	orm::FK<CompAIFlyer> _AIFlyer;
	orm::FK<CompTeam> _team;
	orm::FK<CompSkin> _skin;
	orm::FK<CompHp> _hp;

	virtual void _afterLoad() override;
	virtual void _beforeSave() override;
	virtual void _beforeUpdate() override;

	ORM_MAKE_STATIC_COLUMN(_game, _coordX, _coordY, _type, \
		_AIMain, _AIWarrior, _AIDefender, \
		_AISpawner, _AIWalker, _AIFlyer, \
		_team, _skin, _hp)
};