#pragma once

#include <SFML-utils/Gui.h>
#include <SFML-utils/ES.h>

#include <SFML-Book/Entity.h>

namespace book
{
	class Level;
	class Team;

	class TeamGui
	{
	public:
		TeamGui(const TeamGui&) = delete;
		TeamGui& operator=(const TeamGui&) = delete;

		TeamGui(Team& team, sf::RenderWindow& window, const sf::Color& color);

		void update(sf::Time deltaTime);
		bool processEvent(sf::Event& event);
		void processEvents();
		void draw(sf::RenderTarget& window);

		void setGold(int amount);
		const sf::Color& getColor() const;
		void setLevel(Level* level);

		void setSelected(std::uint32_t id, sfutils::EntityManager<Entity>& manager);

	private:
		Team& _team;

		sfutils::Frame _infoBar;
		sfutils::Label* _labelGold;

		sfutils::Frame _selectBar;
		sfutils::Label* _entityName;
		sfutils::Label* _entityHp;
		sfutils::AnimatedSprite _spriteInfo;

		sfutils::Frame _buildBar;
		sfutils::AnimatedSprite _spriteBuild;
		int _gold_cost;

		using FuncType = std::function<void(Entity& entity, Team* team, Level& level)>;
		FuncType _makeAs;

		std::uint32_t _entityId;
		sfutils::EntityManager<Entity>* _entityManager;

		sf::Color _color;
		Level* _level;

		std::vector<sf::ConvexShape*> _highlight;
		sf::ConvexShape* _selectionLight;

		void initInfoBar();
		void initSelectingBar();
		void initBuildBar();

		enum Status
		{
			None,
			Selecting,
			Building,
			Exit
		} _status;

		void unSelect();
		void unBuild();
		void setBuild();
		void setHp(int current, int max);
	};
}