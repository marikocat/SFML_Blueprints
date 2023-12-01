#pragma once

#include <SFML-book/common/Connection.h>

namespace book
{
	class Team;

	class Client : public Connection
	{
	public:
		Client(const Client&) = delete;
		Client& operator=(const Client&) = delete;

		Client();
		~Client();

		void setTeam(Team* team);
		Team* getTeam() const;

		bool connect();
		virtual sf::IpAddress getRemoteAddress() const;

		sf::TcpSocket& getSockIn();

	private:
		Team* _team;

	};
}