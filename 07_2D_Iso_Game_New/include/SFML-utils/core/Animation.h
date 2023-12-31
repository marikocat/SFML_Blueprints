#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace sfutils
{
	class Animation
	{
	public:
		Animation(const Animation&) = delete;
		Animation& operator=(const Animation&) = delete;

		Animation(sf::Texture* texture = nullptr);
		~Animation();

		void setTexture(sf::Texture* texture);
		sf::Texture* getTexture() const;

		Animation& addFrame(const sf::IntRect& rect);
		Animation& addFramesLine(int number_x, int number_y, int line);
		Animation& addFramesColumn(int number_x, int number_y, int column);

		size_t size() const;
		const sf::IntRect& getRect(size_t index) const;

	private:
		friend class AnimatedSprite;
		std::vector<sf::IntRect> _frames;
		sf::Texture* _texture;

	};
}