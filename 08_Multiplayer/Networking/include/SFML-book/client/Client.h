#pragma once

#include <SFML-book/common/Connection.h>

namespace book
{
	class Client : public Connection
	{
	public:
		Client(const Client&) = delete;
		Client& operator=(const Client&) = delete;

		Client();

		bool connect(const sf::IpAddress& ip, unsigned short port, sf::Time timeout = sf::Time::Zero);

		virtual sf::IpAddress getRemoteAddress() const;

	protected:
		unsigned int _port;

	};
}