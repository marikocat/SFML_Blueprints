#pragma once
#include "Widget.h"

#include <functional>

namespace book
{
	namespace gui
	{
		class Button : public Widget
		{
		public:
			using FuncType = std::function<void(const sf::Event& event, Button& self)>;
			static FuncType defaultFunc;

			Button(Widget* parent = nullptr);
			virtual ~Button();

			FuncType onClick;

		protected:
			virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos) override;
			virtual void onMouseEntered();
			virtual void onMouseLeft();

		private:
			enum Status { None = 0, Hover = 1 };
			int m_status;
		};
	}
}