#include <SFML-book/server/Team.h>

ORM_REGISTER(Team, "Team",\
				_isAlive, "isAlive",\
				_id, "id",\
				_gold, "gold",\
				_colorChar, "color",\
				_game, "game_id")
ORM_M2M_REGISTER(Team, _enemies, Team, "Team_enemies", "team_id", "enemy_id")

Team::Team() : 
	_isAlive(Team::$_isAlive),
	_id(Team::$_id),
	_gold(Team::$_gold),
	_colorChar(Team::$_colorChar),
	_game(Team::$_game),
	_enemies(*this)
{
	_isAlive.registerAttr(*this);
	_id.registerAttr(*this);
	_gold.registerAttr(*this);
	_colorChar.registerAttr(*this);
	_game.registerAttr(*this);
}

Team::Team(int id, const sf::Color& color, int gold, Game::pointer game) : Team()
{
	_isAlive = true;
	_id = id;
	_gold = gold;
	_color = color;
	_game = game;
}

void Team::addGold(int amount)
{
	_gold += amount;
	_game->markTeamUpdated(_id);
}

int Team::getGold() const
{
	return _gold.getValue();
}

void Team::addEnemy(Team::pointer team)
{
	_enemies.add(team);
}

const Team::pointer_array Team::getEnemies()
{
	auto r = _enemies.all();
	return r;
}

void Team::addQgId(std::uint32_t id)
{
	_QGId.emplace_back(id);
}

const std::vector<std::uint32_t>& Team::getQgIds() const
{
	return _QGId;
}

void Team::removeQgId(std::uint32_t id)
{
	std::size_t size = _QGId.size();
	std::size_t i = 0;
	while (i < size)
	{
		if (_QGId[i] == id)
		{
			_QGId.erase(_QGId.begin() + i);
			--size;
		}
		else
			++i;
	}
	_isAlive = _QGId.size() > 0;
}

int Team::id() const
{
	return _id.getValue();
}

const sf::Color& Team::getColor() const
{
	return _color;
}

void Team::add(book::Client* client)
{
	_clients.emplace_back(client);
}

void Team::remove(book::Client* client)
{
	_clients.remove(client);
}

const std::list<book::Client*>& Team::getClients() const
{
	return _clients;
}

bool Team::isGameOver() const
{
	return _isAlive.getValue();
}

void Team::_afterLoad()
{
	std::cout << "Team::_afterLoad() started\n";
	int res = _colorChar.getValue();
	sf::Color c{ sf::Uint32(res) };
	_color.r = c.r;
	_color.g = c.g;
	_color.b = c.b;
	_color.a = c.a;
	std::cout << "Team::_afterLoad() finished\n";
}

void Team::_beforeSave()
{
	_colorChar = _color.toInteger();
}

void Team::_beforeUpdate()
{
	_beforeSave();
}