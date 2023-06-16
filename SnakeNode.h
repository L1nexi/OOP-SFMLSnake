#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	static const sf::Color snake_color(255, 230, 0);

	// inherit from sf::Drawable and sf::Transformable
	// to support syntax window.draw(entity);
	class SnakeNode : public sf::Drawable, public sf::Transformable
	{
	public:
		SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

		// add rotation-related functions for rect_
		void setPosition(sf::Vector2f position);
		void setPosition(const float &x, const float &y);
		void setRotation(const float &angel);
		void setCircleColor(const sf::Color &color = snake_color);
		void setRectColor(const sf::Color &color = sf::Color::Black);
		void move(const float &xOffset, const float &yOffset);
		void rotate(const float &theta);
		void follow(const sfSnake::SnakeNode &node);

		sf::Vector2f getPosition() const;
		float getRotation() const;

		sf::FloatRect getBounds() const;

		const static float NodeRadius;
		const static float MoveDistance;

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
		sf::CircleShape circle_;
		sf::RectangleShape rect_;	//rectangle of snake body
	};

	// inline function
	inline void SnakeNode::setPosition(sf::Vector2f position)
	{
		circle_.setPosition(position);
		rect_.setPosition(position);
	}
	inline void SnakeNode::setPosition(const float &x, const float &y)
	{
		circle_.setPosition(sf::Vector2f(x, y));
		rect_.setPosition(sf::Vector2f(x, y));
	}
	inline void SnakeNode::setRotation(const float &angel)
	{
		rect_.setRotation(angel);
	}
	inline void SnakeNode::setCircleColor(const sf::Color &color)
	{
		circle_.setFillColor(color);
	}
	inline void SnakeNode::setRectColor(const sf::Color &color)
	{
		rect_.setFillColor(color);
	}
	inline void SnakeNode::move(const float &xOffset, const float &yOffset)
	{
		circle_.move(sf::Vector2f(xOffset, yOffset));
		rect_.move(sf::Vector2f(xOffset, yOffset));
	}
	inline void SnakeNode::rotate(const float &theta)
	{
		rect_.rotate(theta);
	}
	inline sf::FloatRect SnakeNode::getBounds() const
	{
		return circle_.getGlobalBounds();
	}
	inline float SnakeNode::getRotation() const
	{
		return rect_.getRotation();
	}
	inline sf::Vector2f SnakeNode::getPosition() const
	{
		return circle_.getPosition();
	}
	inline void SnakeNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(circle_, states);
		target.draw(rect_, states);
	}
} // namespace sfSnake

#endif