namespace book
{
	template<typename T>
	ActionTarget<T>::ActionTarget(const ActionMap<T>& map) : m_actionMap(map)
	{
	}

	template<typename T>
	bool ActionTarget<T>::processEvent(const sf::Event& event) const
	{
		bool res = false;
		for (auto& pair : m_eventsPoll)
		{
			if (m_actionMap.get(pair.first) == event)
			{
				pair.second(event);
				res = true;
				break;
			}
		}
		return res;
	}

	template<typename T>
	void ActionTarget<T>::processEvents() const
	{
		for (auto& pair : m_eventsRealTime)
		{
			const Action& action = m_actionMap.get(pair.first);
			if (action.test())
				pair.second(action.m_event);
		}
	}

	template<typename T>
	void ActionTarget<T>::bind(const T& key, const FuncType& callback)
	{
		const Action& action = m_actionMap.get(key);
		if (action.m_type & Action::Type::RealTime)
			m_eventsRealTime.emplace_back(key, callback);
		else
			m_eventsPoll.emplace_back(key, callback);
	}

	template<typename T>
	void ActionTarget<T>::unbind(const T& key)
	{
		auto remove_func = [&key](const std::pair<T, FuncType>& pair) -> bool
		{
			return pair.first == key;
		};

		const Action& action = m_actionMap.get(key);
		if (action.m_type & Action::Type::RealTime)
			m_eventsRealTime.remove_if(remove_func);
		else
			m_eventsPoll.remove_if(remove_func);
	}
}