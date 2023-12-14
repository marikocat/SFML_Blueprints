#include <SFML-book/server/Component.h>
#include <SFML-book/server/Entity.h>

/////////// CompAIMain ///////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompAIMain, "CompAIMain", \
	_gold_amount, "gold_amount", \
	_deltaAsDouble, "deltaAsDouble", \
	_elapsedAsDouble, "elapsedAsDouble")

CompAIMain::CompAIMain(int gold, const sf::Time& timeDelta) : CompAIMain()
{
	_gold_amount = gold;
	_delta = timeDelta;
	_elapsed = sf::Time::Zero;
}

CompAIMain& CompAIMain::operator=(const CompAIMain& other)
{
	_gold_amount = other._gold_amount;

	_delta = other._delta;
	_deltaAsDouble = other._deltaAsDouble;

	_elapsed = other._elapsed;
	_elapsedAsDouble = other._elapsedAsDouble;

	return *this;
}

void CompAIMain::_afterLoad()
{
	_delta = sf::seconds(_deltaAsDouble);
	_elapsed = sf::seconds(_elapsedAsDouble);
}

void CompAIMain::_beforeSave()
{
	_deltaAsDouble = _delta.asSeconds();
	_elapsedAsDouble = _elapsed.asSeconds();
}

void CompAIMain::_beforeUpdate()
{
	_beforeSave();
}

///////////////////// CompAIWarrior //////////////////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompAIWarrior, "CompAIWarrior",\
	_hitPoint, "hitPoint",\
	_deltaAsDouble, "deltaAsDouble",\
	_elapsedAsDouble, "elapsedAsDouble",\
	_range, "range",\
	_enemyId, "enemyId")

CompAIWarrior::CompAIWarrior(int hitPoint, const sf::Time& timeDelta, int range) : CompAIWarrior()
{
	_hitPoint = hitPoint;
	_delta = timeDelta;
	_elapsed = sf::Time::Zero;
	_range = range;
	_enemyId = -1;
}

CompAIWarrior& CompAIWarrior::operator=(const CompAIWarrior& other)
{
	_hitPoint = other._hitPoint;
	_delta = other._delta;
	_deltaAsDouble = other._deltaAsDouble;
	_elapsed = other._elapsed;
	_elapsedAsDouble = other._elapsedAsDouble;
	_range = other._range;
	_enemyId = other._enemyId;

	return *this;
}

void CompAIWarrior::_afterLoad()
{
	_delta = sf::seconds(_deltaAsDouble);
	_elapsed = sf::seconds(_elapsedAsDouble);
}

void CompAIWarrior::_beforeSave()
{
	_deltaAsDouble = _delta.asSeconds();
	_elapsedAsDouble = _elapsed.asSeconds();
}

void CompAIWarrior::_beforeUpdate()
{
	_beforeSave();
}

///////////////// CompAIDefender //////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompAIDefender, "CompAIDefender",\
	_hitPoint, "hitPoint",\
	_deltaAsDouble, "deltaAsDouble",\
	_elapsedAsDouble, "elapsedAsDouble",\
	_range, "range")

CompAIDefender::CompAIDefender(int hitPoint, const sf::Time& timeDelta, int range) : CompAIDefender()
{
	_hitPoint = hitPoint;
	_delta = timeDelta;
	_elapsed = sf::Time::Zero;
	_range = range;
}

CompAIDefender& CompAIDefender::operator=(const CompAIDefender& other)
{
	_hitPoint = other._hitPoint;
	_delta = other._delta;
	_deltaAsDouble = other._deltaAsDouble;
	_elapsed = other._elapsed;
	_elapsedAsDouble = other._elapsedAsDouble;
	_range = other._range;

	return *this;
}

void CompAIDefender::_afterLoad()
{
	_delta = sf::seconds(_deltaAsDouble);
	_elapsed = sf::seconds(_elapsedAsDouble);
}

void CompAIDefender::_beforeSave()
{
	_deltaAsDouble = _delta.asSeconds();
	_elapsedAsDouble = _elapsed.asSeconds();
}

void CompAIDefender::_beforeUpdate()
{
	_beforeSave();
}

//////////////////////////// CompAISpawner /////////////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompAISpawner, "CompAISpawner",\
	_makeAsTypeId, "makeAsTypeId",\
	_number, "number",\
	_deltaAsDouble, "deltaAsDouble",\
	_elapsedAsDouble, "elapsedAsDouble")

CompAISpawner::CompAISpawner(book::MakeAs makeAs, int number, const sf::Time& timeDelta) : CompAISpawner()
{
	_makeAs = makeAs;
	_number = number;
	_delta = timeDelta;
	_elapsed = sf::Time::Zero;
}

CompAISpawner& CompAISpawner::operator=(const CompAISpawner& other)
{
	_makeAs = other._makeAs;
	_makeAsTypeId = other._makeAsTypeId;
	_number = other._number;
	_delta = other._delta;
	_deltaAsDouble = other._deltaAsDouble;
	_elapsed = other._elapsed;
	_elapsedAsDouble = other._elapsedAsDouble;

	return *this;
}

void CompAISpawner::_afterLoad()
{
	_makeAs = book::getMakeAs(_makeAsTypeId);
	_delta = sf::seconds(_deltaAsDouble);
	_elapsed = sf::seconds(_elapsedAsDouble);
}

void CompAISpawner::_beforeSave()
{
	_makeAsTypeId = book::getType(_makeAs);
	_deltaAsDouble = _delta.asSeconds();
	_elapsedAsDouble = _elapsed.asSeconds();
}

void CompAISpawner::_beforeUpdate()
{
	_beforeSave();
}

////////////////////////////// CompAIWalker ////////////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompAIWalker, "CompAIWalker",\
	_speed, "speed",\
	_pathToTakeX, "pathToTakeX",\
	_pathToTakeY, "pathToTakeY")

CompAIWalker::CompAIWalker(float speed) : CompAIWalker()
{
	_speed = speed;
}

CompAIWalker& CompAIWalker::operator=(const CompAIWalker& other)
{
	_speed = other._speed;
	_pathToTake = other._pathToTake;
	_pathToTakeX = other._pathToTakeX;
	_pathToTakeY = other._pathToTakeY;

	return *this;
}

void CompAIWalker::_afterLoad()
{
	_pathToTake.x = _pathToTakeX;
	_pathToTake.y = _pathToTakeY;
}

void CompAIWalker::_beforeSave()
{
	_pathToTakeX = _pathToTake.x;
	_pathToTakeY = _pathToTake.y;
}

void CompAIWalker::_beforeUpdate()
{
	_beforeSave();
}

/////////////////// CompAIFlyer /////////////////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompAIFlyer, "CompAIFlyer",\
	_speed, "speed",\
	_pathToTakeX, "pathToTakeX",\
	_pathToTakeY, "pathToTakeY")

CompAIFlyer::CompAIFlyer(float speed) : CompAIFlyer()
{
	_speed = speed;
}

CompAIFlyer& CompAIFlyer::operator=(const CompAIFlyer& other)
{
	_speed = other._speed;
	_pathToTake = other._pathToTake;
	_pathToTakeX = other._pathToTakeX;
	_pathToTakeY = other._pathToTakeY;

	return *this;
}

void CompAIFlyer::_afterLoad()
{
	_pathToTake.x = _pathToTakeX;
	_pathToTake.y = _pathToTakeY;
}

void CompAIFlyer::_beforeSave()
{
	_pathToTakeX = _pathToTake.x;
	_pathToTakeY = _pathToTake.y;
}

void CompAIFlyer::_beforeUpdate()
{
	_beforeSave();
}

////////////// CompTeam ////////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompTeam, "CompTeam",\
	_team, "team")

CompTeam::CompTeam(Team::pointer team) : CompTeam()
{
	_team = team;
}

CompTeam& CompTeam::operator=(const CompTeam& other)
{
	_team = other._team;
	return *this;
}

///////////////// CompSkin /////////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompSkin, "CompSkin",\
	_animationId, "animationId")

CompSkin::CompSkin(short int animation) : CompSkin()
{
	_animationId = animation;
}

CompSkin& CompSkin::operator=(const CompSkin& other)
{
	_animationId = other._animationId;
	return *this;
}

/////////////////// CompHp ///////////////////////

// This macro will construct the entire default constructor implementation.
ORM_REGISTER_AND_CONSTRUCT(CompHp, "CompHp",\
	_hp, "hp",\
	_maxHp, "maxHp")

CompHp::CompHp(int hp) : CompHp()
{
	_hp = hp;
	_maxHp = hp;
}

CompHp& CompHp::operator=(const CompHp& other)
{
	_hp = other._hp;
	_maxHp = other._maxHp;
	return *this;
}