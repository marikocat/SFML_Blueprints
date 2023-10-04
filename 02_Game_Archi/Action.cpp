#include <cstring>
#include "Action.h"

namespace book
{
	Action::Action(const Action& other) : m_type(other.m_type)
	{
		std::memcpy(&m_event, &other.m_event, sizeof(sf::Event));
	}
	Action& Action::operator=(const Action& other)
	{
		std::memcpy(&m_event, &other.m_event, sizeof(sf::Event));
		m_type = other.m_type;
		return *this;
	}

	Action::Action(const sf::Keyboard::Key& key, int type) : m_type(type)
	{
		m_event.type = sf::Event::EventType::KeyPressed;
		m_event.key.code = key;
	}
	Action::Action(const sf::Mouse::Button& button, int type) : m_type(type)
	{
		m_event.type = sf::Event::EventType::MouseButtonPressed;
		m_event.mouseButton.button = button;
	}

	bool Action::test() const
	{
		bool res = false;
		if (m_event.type == sf::Event::EventType::KeyPressed)
		{
			if (m_type & Type::Pressed)
				res = sf::Keyboard::isKeyPressed(m_event.key.code);
		}
		else if (m_event.type == sf::Event::EventType::MouseButtonPressed)
		{
			if (m_type & Type::Pressed)
				res = sf::Mouse::isButtonPressed(m_event.mouseButton.button);
		}
		return res;
	}

	bool Action::operator==(const sf::Event& event) const
	{
		bool res = false;
		switch (event.type)
		{
		case sf::Event::EventType::KeyPressed:
		{
			if (m_type & Type::Pressed and m_event.type == sf::Event::EventType::KeyPressed)
				res = event.key.code == m_event.key.code;
		} break;
		case sf::Event::EventType::KeyReleased:
		{
			if (m_type & Type::Released and m_event.type == sf::Event::EventType::KeyPressed)
				res = event.key.code == m_event.key.code;
		} break;
		case sf::Event::EventType::MouseButtonPressed:
		{
			if (m_type & Type::Pressed and m_event.type == sf::Event::EventType::MouseButtonPressed)
				res = event.mouseButton.button == m_event.mouseButton.button;
		} break;
		case sf::Event::EventType::MouseButtonReleased:
		{
			if (m_type & Type::Released and m_event.type == sf::Event::EventType::MouseButtonPressed)
				res = event.mouseButton.button == m_event.mouseButton.button;
		} break;
		default: break;
		}
		return res;
	}
	bool Action::operator==(const Action& other) const
	{
		return m_type == other.m_type and other == m_event;
	}
}