#pragma once
#include "Action.h"

#include <unordered_map>

namespace book
{
	template<typename T = int>
	class ActionMap
	{
	public:
		ActionMap(const ActionMap<T>&) = delete;
		ActionMap<T>& operator=(const ActionMap<T>&) = delete;

		ActionMap() = default;

		void map(const T& key, const Action& action);
		const Action& get(const T& key) const;

	private:
		std::unordered_map<T, Action> m_map;
	};
}

#include "ActionMap.tpl"