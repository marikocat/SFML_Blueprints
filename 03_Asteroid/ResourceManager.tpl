#include <stdexcept>
#include <utility>

namespace book
{
	template<typename RESOURCE, typename IDENTIFIER>
	template<typename ... Args>
	void ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
	{
		std::unique_ptr<RESOURCE> ptr(new RESOURCE);
		if (not ptr->loadFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Impossible to load file");
		m_map.emplace(id, std::move(ptr));
	}

	template<typename RESOURCE, typename IDENTIFIER>
	RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id) const
	{
		return *m_map.at(id);
	}

	// sf::Music special case
	template<typename IDENTIFIER>
	template<typename ... Args>
	void ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
	{
		std::unique_ptr<sf::Music> ptr(new sf::Music);
		if (not ptr->openFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Impossible to open file");
		m_map.emplace(id, std::move(ptr));
	}

	template<typename IDENTIFIER>
	sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
	{
		return *m_map.at(id);
	}
}