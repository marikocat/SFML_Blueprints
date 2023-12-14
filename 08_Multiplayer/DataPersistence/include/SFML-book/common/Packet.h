#pragma once

#include <SFML-book/common/FuncIds.h>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include <list>

namespace book
{
	namespace packet
	{
		// base
		class NetworkEvent
		{
		public:
			NetworkEvent(FuncIds::FUNCIDS type);
			virtual ~NetworkEvent();

			FuncIds::FUNCIDS type() const;

			static NetworkEvent* makeFromPacket(sf::Packet& packet);

			friend sf::Packet& operator>>(sf::Packet&, NetworkEvent& self);
			friend sf::Packet& operator<<(sf::Packet&, const NetworkEvent& self);

		protected:
			const FuncIds::FUNCIDS _type;

		};

		// specials

		class Disconnected : public NetworkEvent
		{
		public:
			Disconnected();
		};

		class LogOut : public NetworkEvent
		{
		public:
			LogOut();
		};

		// main menu
		class GetListGame : public NetworkEvent
		{
		public:
			GetListGame();
		};

		class SetListGame : public NetworkEvent
		{
		public:
			SetListGame();

			friend sf::Packet& operator>>(sf::Packet& packet, SetListGame& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const SetListGame& self);

			struct Game
			{
				int nbTeams;
				int nbPlayers;
				int id;
			};

			void add(int id, int players, int teams);
			const std::list<Game> list() const;

		private:
			std::list<Game> _list;

		};

		class CreateGame : public NetworkEvent
		{
		public:
			CreateGame();
		};

		class JoinGame : public NetworkEvent
		{
		public:
			JoinGame();
			JoinGame(int gameId);

			int gameId() const;

			friend sf::Packet& operator>>(sf::Packet& packet, JoinGame& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const JoinGame& self);

		private:
			int _gameId;

		};

		class JoinGameConfirmation : public NetworkEvent
		{
		public:
			JoinGameConfirmation();
			JoinGameConfirmation(const std::string& mapDatas, int team);

			const std::string& getMapDatas() const;
			int getTeamId() const;

			friend sf::Packet& operator>>(sf::Packet& packet, JoinGameConfirmation& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const JoinGameConfirmation& self);

			struct Data
			{
				int team;
				int gold;
				sf::Color color;
			};

			const void addTeam(Data&& data);
			const std::list<Data>& getTeamInfo() const;

		private:
			std::string _mapDatas;
			int _teamId;
			std::list<Data> _teamInfo;

		};

		class JoinGameReject : public NetworkEvent
		{
		public:
			JoinGameReject();
			JoinGameReject(int id);

			int gameId() const;

			friend sf::Packet& operator>>(sf::Packet& packet, JoinGameReject& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const JoinGameReject& self);

		private:
			int _gameId;

		};

		// in game
		class RequestCreateEntity : public NetworkEvent
		{
		public:
			RequestCreateEntity();
			RequestCreateEntity(short int type, const sf::Vector2i& coord);

			short int getType() const;
			const sf::Vector2i& getCoord() const;

			friend sf::Packet& operator>>(sf::Packet& packet, RequestCreateEntity& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const RequestCreateEntity& self);

		private:
			short int _entityType;
			sf::Vector2i _coord;

		};

		class RequestDestroyEntity : public NetworkEvent
		{
		public:
			RequestDestroyEntity();
			RequestDestroyEntity(unsigned int id);

			unsigned int getId() const;

			friend sf::Packet& operator>>(sf::Packet& packet, RequestDestroyEntity& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const RequestDestroyEntity& self);

		private:
			unsigned int _id;

		};

		class DestroyEntity : public NetworkEvent
		{
		public:
			DestroyEntity();

			void add(unsigned int id);
			const std::list<unsigned int>& getDestroy() const;

			friend sf::Packet& operator>>(sf::Packet& packet, DestroyEntity& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const DestroyEntity& self);

		private:
			std::list<unsigned int> _updates;

		};

		class CreateEntity : public NetworkEvent
		{
		public:
			CreateEntity();

			struct Data
			{
				unsigned int entityId;
				short int entityType;
				short int entityTeam;
				short int animationId;
				sf::Vector2f position;
				sf::Vector2i coord;
				int maxHp;
				int hp;
			};

			void add(Data&& update);
			const std::list<Data>& getCreates() const;
			void clear();

			friend sf::Packet& operator>>(sf::Packet& packet, CreateEntity& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const CreateEntity& self);

		private:
			std::list<Data> _updates;

		};

		class UpdateEntity : public NetworkEvent
		{
		public:
			UpdateEntity();

			struct Data
			{
				unsigned int entityId;
				short int animationId;
				sf::Vector2f position;
				sf::Vector2i coord;
				int hp;
			};

			void add(Data&& update);
			const std::list<Data>& getUpdates() const;
			void clear();

			friend sf::Packet& operator>>(sf::Packet& packet, UpdateEntity& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const UpdateEntity& self);

		private:
			std::list<Data> _updates;

		};

		class OnHittedEntity : public NetworkEvent
		{
		public:
			OnHittedEntity();

			struct Data
			{
				unsigned int entityId;
				sf::Vector2i entityCoord;
				unsigned int enemyId;
				sf::Vector2i enemyCoord;
			};

			void add(Data&& data);
			const std::list<Data>& getHitted() const;

			friend sf::Packet& operator>>(sf::Packet& packet, OnHittedEntity& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const OnHittedEntity& self);

		private:
			std::list<Data> _updates;

		};

		class OnHitEntity : public NetworkEvent
		{
		public:
			OnHitEntity();

			struct Data
			{
				unsigned int entityId;
				sf::Vector2i entityCoord;
				unsigned int enemyId;
				sf::Vector2i enemyCoord;
			};

			void add(Data&& data);
			const std::list<Data>& getHit() const;

			friend sf::Packet& operator>>(sf::Packet& packet, OnHitEntity& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const OnHitEntity& self);

		private:
			std::list<Data> _updates;

		};

		class OnSpawnEntity : public NetworkEvent
		{
		public:
			OnSpawnEntity();

			void add(unsigned int id);
			const std::list<unsigned int>& getSpawn() const;

			friend sf::Packet& operator>>(sf::Packet& packet, OnSpawnEntity& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const OnSpawnEntity& self);

		private:
			std::list<unsigned int> _updates;

		};

		class UpdateTeam : public NetworkEvent
		{
		public:
			UpdateTeam();

			struct Data
			{
				short int team;
				bool gameOver;
				int gold;
			};

			void add(Data&& update);
			const std::list<Data>& getUpdates() const;

			friend sf::Packet& operator>>(sf::Packet& packet, UpdateTeam& self);
			friend sf::Packet& operator<<(sf::Packet& packet, const UpdateTeam& self);

		private:
			std::list<Data> _updates;

		};
	}
}