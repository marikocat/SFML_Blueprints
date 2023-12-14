#pragma once

#include <vector>
#include <list>
#include <cstdint>

#include <SFML/Graphics.hpp>

#include <ORM/fields.hpp>
#include <ORM/fields/ManyToMany.hpp>
#include <ORM/models/SqlObject.hpp>

#include <SFML-book/server/Game.h>

namespace book
{
	class Client;
}

class Team : public orm::SqlObject<Team>
{
public:
	Team(const Team&) = delete;
	Team& operator=(const Team&) = delete;

	Team();
	Team(int id, const sf::Color& color, int gold, Game::pointer game);

	void addGold(int amount);
	int getGold() const;

	void addEnemy(Team::pointer team);
	const Team::pointer_array getEnemies();

	void addQgId(std::uint32_t id);
	const std::vector<std::uint32_t>& getQgIds() const;
	void removeQgId(std::uint32_t id);

	int id() const;
	const sf::Color& getColor() const;

	void add(book::Client* client);
	void remove(book::Client* client);

	const std::list<book::Client*>& getClients() const;

	bool isGameOver() const;

	ORM_MAKE_STATIC_COLUMN(_id, _isAlive, _gold, _game, _colorChar)

private:
	orm::BooleanField _isAlive;
	orm::IntegerField _id;
	orm::IntegerField _gold;
	orm::IntegerField _colorChar;

	std::vector<std::uint32_t> _QGId;
	sf::Color _color;

	orm::FK<Game> _game;

	orm::ManyToMany<Team, Team> _enemies;

	std::list<book::Client*> _clients;

	virtual void _afterLoad() override;
	virtual void _beforeSave() override;
	virtual void _beforeUpdate() override;

};