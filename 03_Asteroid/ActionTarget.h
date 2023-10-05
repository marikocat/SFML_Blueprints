#pragma once
#include <functional>
#include <utility>
#include <list>
#include "ActionMap.h"

namespace book
{
	template<typename T = int>
	class ActionTarget
	{
	public:
		ActionTarget(const ActionTarget<T>&) = delete;
		ActionTarget<T>& operator=(const ActionTarget<T>&) = delete;

		using FuncType = std::function<void(const sf::Event&)>;

		ActionTarget(const ActionMap<T>& map);

		bool processEvent(const sf::Event& event) const;
		void processEvents() const;

		void bind(const T& key, const FuncType& callback);
		void unbind(const T& key);

	private:
		std::list<std::pair<T, FuncType>> m_eventsRealTime;
		std::list<std::pair<T, FuncType>> m_eventsPoll;

		const ActionMap<T>& m_actionMap;
	};
}
#include "ActionTarget.tpl"