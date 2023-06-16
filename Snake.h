#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	// add direction class
	// for mouse control
	class Direction
	{
	public:
		Direction(const float &angel = 0.f) : angle_(angel) {}
		void update(const sf::Vector2f &lhs, const sf::Vector2f &rhs);
		void update(const float &angel);
		float asAngle() const { return angle_; }
		sf::Vector2f asVector() const;
		const static Direction Left;
		const static Direction Right;
		const static Direction Up;
		const static Direction Down;
		// direction constants
	private:
		// in window coordinate
		// already applied vertical flip of y-axis
		// in angel instead of radian
		float angle_{0.f};
	};

	// for syntax window.draw(snake)
	class Snake : public sf::Drawable, public sf::Transformable
	{
	public:
		Snake();

		void handleInput(sf::RenderWindow &window);
		void update(const sf::Time &delta);
		bool checkFruitCollisions(std::vector<Fruit> &fruits);
		bool checkBodyBlock(const sf::FloatRect &bounds) const;
		float getAngel() const { return direction_.asAngle(); };
		bool hitSelf() const;

		unsigned getSize() const;

	private:
		void move();
		void grow(const Fruit &fruit);
		void checkEdgeCollisions();
		void checkSelfCollisions();
		void initNodes();
		void updateDirection(const sf::Vector2f &mousePos);
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		sf::SoundBuffer pickupBuffer_;
		sf::Sound pickupSound_;

		sf::SoundBuffer dieBuffer_;
		sf::Sound dieSound_;

		Direction direction_;
		bool hitSelf_;
		std::vector<SnakeNode> nodes_;

		sf::Texture headTexture_;
		sf::Sprite head_;

		static const int InitialSize;
		static const int CheckBegin;
	};

	inline bool operator==(const Direction &lhs, const Direction &rhs)
	{
		return lhs.asAngle() == rhs.asAngle();
	}
	inline bool operator!=(const Direction &lhs, const Direction &rhs)
	{
		return !(lhs == rhs);
	}
	inline bool Snake::hitSelf() const
	{
		return hitSelf_;
	}

	inline unsigned Snake::getSize() const
	{
		return nodes_.size();
	}
}

#endif