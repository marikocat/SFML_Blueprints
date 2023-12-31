#pragma once
#include "Container.h"
#include "ActionTarget.h"

namespace book
{
	namespace gui
	{
		class Frame : public Container, protected ActionTarget<int>
		{
		public:
			Frame(const Frame&) = delete;
			Frame& operator=(const Frame&) = delete;

			using ActionTarget<int>::FuncType;

			Frame(sf::RenderWindow& window);
			virtual ~Frame();

			bool processEvent(const sf::Event& event);
			void processEvents();

			void bind(int key, const FuncType& callback);
			void unbind(int key);

			void draw();
			virtual sf::Vector2f getSize() const override;

		private:
			sf::RenderWindow& m_window;

			virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) override;
			virtual void processEvents(const sf::Vector2f& parent_pos) override;
		};
	}
}