#pragma once

#include <SFML-utils/es/defines.h>
#include <utils/memory_utils.h>

#include <list>
#include <vector>
#include <bitset>
#include <cstdint>
#include <tuple>
#include <algorithm>
#include <cassert>

namespace sfutils
{
	namespace es
	{
		template<typename COMPONENT, typename ENTITY> class ComponentHandle;
		template<typename COMPONENT, typename ENTITY> class Component;

		template<class ENTITY>
		class EntityManager
		{
			template<typename ...> class View;

		public:
			using container = std::list<std::uint32_t>;

			EntityManager(const EntityManager&) = delete;
			EntityManager& operator=(const EntityManager&) = delete;

			EntityManager();
			~EntityManager();

			template<typename ... Args>
			std::uint32_t create(Args&& ... args);

			template<typename ... Args>
			void emplace(std::uint32_t id, Args&& ... args);

			void remove(std::uint32_t id);

			void update();

			void reset();

			std::size_t size() const;

			bool isValid(std::uint32_t id) const;

			const ENTITY& get(std::size_t id) const;
			ENTITY& get(std::size_t id);

			const ENTITY* getPtr(std::size_t id) const;
			ENTITY* getPtr(std::size_t id);

			container::const_iterator begin() const;
			container::const_iterator end() const;

			template<typename COMPONENT, typename ... Args>
			void addComponent(std::uint32_t id, Args&& ... args);

			template<typename COMPONENT>
			void removeComponent(std::uint32_t id);

			template<typename COMPONENT>
			bool hasComponent(std::uint32_t id) const;

			template<typename COMPONENT>
			ComponentHandle<COMPONENT, ENTITY> getComponent(std::uint32_t id) const;

			template<typename ... COMPONENT>
			std::tuple<ComponentHandle<COMPONENT, ENTITY>...> getComponents(std::uint32_t id) const;

			template<typename ... COMPONENT>
			View<COMPONENT...> getByComponents(ComponentHandle<COMPONENT, ENTITY>& ... components);

		private:
			std::vector<ENTITY*> _entitiesAllocated;
			std::vector<std::bitset<MAX_COMPONENTS>> _entitiesComponentsMask;
			std::vector<utils::memory::VPool*> _componentsEntities;

			container _entitiesIndex;
			container _entitiesIndexFree;
			container _entitiesIndexToDestroy;

			void reset(std::uint32_t id);

			template<typename COMPONENT>
			void checkComponent();

			template<typename, typename> friend class ComponentHandle;

			template<typename COMPONENT>
			COMPONENT* getComponentPtr(std::uint32_t id) const;

			template<typename ... COMPONENT>
			class View
			{
				class iterator;
			public:
				View(EntityManager<ENTITY>& manager, const std::bitset<MAX_COMPONENTS>& mask, ComponentHandle<COMPONENT, ENTITY>& ... components);

				iterator begin()
				{
					auto begin = _manager._entitiesIndex.begin();
					auto end = _manager._entitiesIndex.end();

					while (begin != end)
					{
						std::uint32_t index = *begin;
						if ((_manager._entitiesComponentsMask[index] & _mask) == _mask)
						{
							unpackId<0, COMPONENT...>(index);
							break;
						}
						++begin;
					}

					return iterator(*this, begin, end);
				}

				iterator end()
				{
					return iterator(*this, _manager._entitiesIndex.end(), _manager._entitiesIndex.end());
				}

			private:
				class iterator
				{
				public:
					iterator(View& view, EntityManager<ENTITY>::container::iterator it, EntityManager<ENTITY>::container::iterator it_end);

					iterator& operator++() //prefix increment
					{
						++_it;
						while (_it != _itEnd)
						{
							std::uint32_t index = *_it;
							if (_view._manager._entitiesAllocated.at(index) != nullptr and
								(_view._manager._entitiesComponentsMask.at(index) & _view._mask) == _view._mask)
							{
								_view.unpackId<0, COMPONENT...>(index);
								break;
							}
							++_it;
						}
						return *this;
					}

					ENTITY* operator*() const;
					ENTITY* operator->() const;
					bool operator==(const iterator& other);
					bool operator!=(const iterator& other);

				private:
					View& _view;
					EntityManager<ENTITY>::container::iterator _it;
					EntityManager<ENTITY>::container::iterator _itEnd;

				};

				template<int N, typename C>
				void unpackId(std::uint32_t id);

				template<int N, typename C0, typename C1, typename ... Cx>
				void unpackId(std::uint32_t id);

				template<int N, typename C>
				void unpackManager();

				template<int N, typename C0, typename C1, typename ... Cx>
				void unpackManager();

				EntityManager<ENTITY>& _manager;
				const std::bitset<MAX_COMPONENTS> _mask;
				std::tuple<ComponentHandle<COMPONENT, ENTITY>&...> _handles;

			};

		};
	}
}
#include <SFML-utils/es/EntityManager.tpl>