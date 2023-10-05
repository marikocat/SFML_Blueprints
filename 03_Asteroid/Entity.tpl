#include <utility>

namespace book
{
	template<typename ... Args>
	void Entity::setPosition(Args&& ... args)
	{
		m_sprite.setPosition(std::forward<Args>(args)...);
	}
}