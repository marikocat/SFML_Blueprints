#include <SFML-book/server/Client.h>

#include <SFML-book/common/FuncIds.h>

#include <SFML-book/server/Team.h>

#include <iostream>

namespace book
{
	Client::Client() : _team(nullptr)
	{
	}

	Client::~Client()
	{
		if (_team)
			_team->remove(this);
	}

	void Client::setTeam(Team* team)
	{
		if (_team)
			_team->remove(this);
		_team = team;
		if (_team)
			_team->add(this);
	}

	Team* Client::getTeam() const
	{
		return _team;
	}

	bool Client::connect()
	{
		bool res = false;
		sf::Packet packet;
		std::cout << "Get datas" << std::endl;
		if (_sockIn.receive(packet) == sf::Socket::Done)
		{
			sf::Int32 fid;

			packet >> fid;
			std::cout << "Receive datas. Compare them to expected one" << std::endl;
			if (fid == FuncIds::IdHandler)
			{
				sf::Uint32 port;
				packet >> port;
				std::cout << "Connect to a given port (" << port << ")" << std::endl;
				if (_sockOut.connect(_sockIn.getRemoteAddress(), port, sf::seconds(5)) == sf::Socket::Done)
				{
					std::cout << "All is good" << std::endl;
					res = true;
				}
				else
					std::cout << "Failed" << std::endl;
			}
			else
				std::cout << "Error. Function id is not IdHandler" << std::endl;
		}
		else
			std::cout << "Failed" << std::endl;
		return res;
	}

	sf::IpAddress Client::getRemoteAddress() const
	{
		return _sockIn.getRemoteAddress();
	}

	sf::TcpSocket& Client::getSockIn()
	{
		return _sockIn;
	}
}