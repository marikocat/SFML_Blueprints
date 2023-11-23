#pragma once

#include <SFML/Audio.hpp>

#include <SFML-utils/core/Animation.h>

#include <unordered_map>
#include <string>
#include <memory>

namespace sfutils
{
	template<typename RESOURCE, typename IDENTIFIER = int>
	class ResourceManager
	{
	public:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		RESOURCE& load(const IDENTIFIER& id, Args&& ... args);

		bool count(const IDENTIFIER& id) const;

		RESOURCE& get(const IDENTIFIER& id) const;

		template<typename ... Args>
		RESOURCE& getOrLoad(const IDENTIFIER& id, Args&& ... args);

		void clear();

	private:
		std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;

	};

	// Partial specialization

	template<typename IDENTIFIER>
	class ResourceManager<sf::Music, IDENTIFIER>
	{
	public:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		sf::Music& load(const IDENTIFIER& id, Args&& ... args);

		bool count(const IDENTIFIER& id) const;

		sf::Music& get(const IDENTIFIER& id) const;

		template<typename ... Args>
		sf::Music& getOrLoad(const IDENTIFIER& id, Args&& ... args);

		void clear();

	private:
		std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>> _map;

	};

	template<typename IDENTIFIER>
	class ResourceManager<Animation, IDENTIFIER>
	{
	public:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		Animation& load(const IDENTIFIER& id, Args&& ... args);

		bool count(const IDENTIFIER& id) const;

		Animation& get(const IDENTIFIER& id) const;

		template<typename ... Args>
		Animation& getOrLoad(const IDENTIFIER& id, Args&& ... args);

		void clear();

	private:
		std::unordered_map<IDENTIFIER, std::unique_ptr<Animation>> _map;

	};
}
#include <SFML-utils/core/ResourceManager.tpl>