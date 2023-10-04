#pragma once

namespace book
{
	template<typename ... Args>
	void Player::setPosition(Args&& ... args)
	{
		m_ship.setPosition(std::forward<Args>(args) ...);
	}
}