#pragma once

#include <SFML-book/common/Connection.h>
#include <SFML-book/server/Team.h>

namespace book
{
	class Client : public Connection
	{
	public:
		Client(const Client&) = delete;
		Client& operator=(const Client&) = delete;

		Client();
		~Client();

		void setTeam(Team::pointer team);
		Team::pointer getTeam() const;

		bool connect();
		virtual sf::IpAddress getRemoteAddress() const override;

		sf::TcpSocket& getSockIn();

	private:
		Team::pointer _team;

	};
}