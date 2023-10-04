#pragma once

namespace book
{
	template<typename T>
	void ActionMap<T>::map(const T& key, const Action& action)
	{
		m_map.emplace(key, action);
	}

	template<typename T>
	const Action& ActionMap<T>::get(const T& key) const
	{
		return m_map.at(key);
	}
}