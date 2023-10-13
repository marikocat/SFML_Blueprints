#include "Widget.h"

namespace book
{
	namespace gui
	{
		Widget::Widget(Widget* parent) : m_parent(parent) {}
		Widget::~Widget() {}

		void Widget::setPosition(const sf::Vector2f& pos)
		{
			m_position = pos;
		}

		void Widget::setPosition(float x, float y)
		{
			m_position.x = x;
			m_position.y = y;
		}

		const sf::Vector2f& Widget::getPosition() const
		{
			return m_position;
		}

		bool Widget::processEvent(const sf::Event& event, const sf::Vector2f& parent_pos)
		{
			return false;
		}

		void Widget::processEvents(const sf::Vector2f& parent_pos) {}

		void Widget::updateShape()
		{
			if (m_parent)
				m_parent->updateShape();
		}
	}
}