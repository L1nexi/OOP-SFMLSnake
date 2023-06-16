#include <SFML/Graphics.hpp>
#include <cmath>
#include "SnakeNode.h"
#define RECT_WIDTH 14.f
#define RECT_HEIGHT 39.59797974644666f

using namespace sfSnake;

const float SnakeNode::NodeRadius = 21.f;
const float SnakeNode::MoveDistance = 28.f;

SnakeNode::SnakeNode(sf::Vector2f position)
{
	circle_.setOrigin(sf::Vector2f(NodeRadius, NodeRadius));
	circle_.setPosition(position);
	circle_.setFillColor(snake_color);
	circle_.setRadius(float(NodeRadius));
	// circle_.setOutlineColor(sf::Color::White);
	// circle_.setOutlineThickness(-1.f);
	rect_.setOrigin(sf::Vector2f(RECT_WIDTH / 2.f, RECT_HEIGHT / 2.f));
	rect_.setPosition(position);
	rect_.setFillColor(sf::Color::Black);
	rect_.setSize(sf::Vector2f(RECT_WIDTH, RECT_HEIGHT));
	// initialize angel toward DOWN
	rect_.setRotation(90.f);
}

void SnakeNode::follow(const sfSnake::SnakeNode &node)
{
	circle_.setPosition(node.getPosition());
	rect_.setPosition(node.getPosition());
	rect_.setRotation(node.getRotation());
}
