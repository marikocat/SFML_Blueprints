#pragma once

#include <SFML-utils/ES.h>
#include <SFML-utils/Map.h>
#include <SFML-utils/Core.h>

#include <SFML-book/common/Packet.h>

namespace book
{
	class Level;
	class Team;

	// base class for put Entity and Effect in same map
	class MapComponent : public sf::Drawable
	{
	public:
		virtual sf::Vector2f getPosition() const = 0;
		virtual void setPosition(const sf::Vector2f& pos) = 0;
	};

	class Entity : public MapComponent, public sfutils::Entity<Entity>
	{
	public:
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		Entity(sfutils::EntityManager<Entity>* manager, std::uint32_t id);

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(const sf::Vector2f& pos) override;

		std::string name;

		using FuncType = std::function<void(Entity& self, const sf::Vector2i& myCoord, Entity& enemy, const sf::Vector2i& enemyCoord, Level& level)>;

		FuncType onHit;
		FuncType onHitted;

		short int type;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};

	void makeAs(unsigned int entityType, Entity& e, Team* team, Level& level, const packet::CreateEntity::Data& data);

	void makeAsMain(Entity& entity, Team* team, Level& level, const packet::CreateEntity::Data& data);
	void makeAsEye(Entity& entity, Team* team, Level& level, const packet::CreateEntity::Data& data);
	void makeAsWormEgg(Entity& entity, Team* team, Level& level, const packet::CreateEntity::Data& data);
	void makeAsWorm(Entity& entity, Team* team, Level& level, const packet::CreateEntity::Data& data);
	void makeAsCarnivor(Entity& entity, Team* team, Level& level, const packet::CreateEntity::Data& data);

	class Effect : public MapComponent
	{
	public:
		Effect(int animationId);

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(const sf::Vector2f& pos);

		sfutils::AnimatedSprite sprite;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};

	Effect* makeBloodEffect();
	Effect* makeFlashEffect();
	Effect* makeVoltageEffect();
}