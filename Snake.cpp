#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

void Direction::update(const sf::Vector2f &begin, const sf::Vector2f &end)
{
	if (begin.x == end.x)
	{
		if (begin.y > end.y)
			angle_ = Direction::Down.angle_;
		else if (begin.y < end.y)
			angle_ = Direction::Up.angle_;
	}
	else
	{
		angle_ = atan2(end.y - begin.y, end.x - begin.x) * 180.f / acos(-1);
		if (angle_ < 0)
			angle_ += 360.f;
	}
}
void Direction::update(const float &angel)
{
	angle_ = angel;
	while (angle_ < 0)
		angle_ += 360.f;
	while (angle_ >= 360.f)
		angle_ -= 360.f;
}

sf::Vector2f Direction::asVector() const
{
	return sf::Vector2f(cos(angle_ * acos(-1) / 180.f), sin(angle_ * acos(-1) / 180.f));
}

const Direction Direction::Left{180.f};
const Direction Direction::Right{0.f};
const Direction Direction::Up{90.f};
const Direction Direction::Down{270.f};

////////////////////////////////////////////////////////////
const int Snake::InitialSize = 6;
const int Snake::CheckBegin = 4;

// TODO texture selection
Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);

}

void Snake::handleInput(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (direction_ != Direction::Up)
			direction_ = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (direction_ != Direction::Down)
			direction_ = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (direction_ != Direction::Right)
			direction_ = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (direction_ != Direction::Left)
			direction_ = Direction::Right;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousepos = sf::Mouse::getPosition(window);
		updateDirection(sf::Vector2f(mousepos.x, mousepos.y));
	}
}
void Snake::update(const sf::Time &delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

bool Snake::checkFruitCollisions(std::vector<Fruit> &fruits)
{
	auto toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
		{
			toRemove = it;
			break;
		}
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		grow(*toRemove);
		fruits.erase(toRemove);
		return true;
	}
	return false;
}

void Snake::move()
{
	for (auto itr = nodes_.rbegin(); itr != nodes_.rend() - 1; ++itr)
	{
		itr->follow(*(itr + 1));
	}

	SnakeNode &headnode = nodes_.front();
	float xoffset = cos(direction_.asAngle() * acos(-1) / 180.f) * SnakeNode::MoveDistance;
	float yoffset = sin(direction_.asAngle() * acos(-1) / 180.f) * SnakeNode::MoveDistance;
	headnode.move(xoffset, yoffset);
	headnode.setRotation(direction_.asAngle());
	head_.setRotation(direction_.asAngle());
	head_.setPosition(headnode.getPosition());
}

void Snake::grow(const Fruit &fruit)
{
	int num = fruit.bonusLength();
	for (int i = 0; i < num; ++i)
	{
		nodes_.emplace_back(nodes_.back().getPosition());
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode &headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::checkSelfCollisions()
{
	SnakeNode &headNode = nodes_[0];

	for (auto itr = nodes_.begin() + CheckBegin; itr != nodes_.end(); ++itr)
	{
		if (headNode.getBounds().intersects((*itr).getBounds()) == true)
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
			break;
		}
	}
}
// check whether the object is blocked by the body
bool Snake::checkBodyBlock(const sf::FloatRect &bounds) const
{
	for (auto itr = nodes_.begin(); itr != nodes_.end(); ++itr)
	{
		if ((bounds.intersects(itr->getBounds())) == true)
			return true;
	}
	return false;
}

void Snake::initNodes()
{
	
	headTexture_.loadFromFile("Textures/head.png");
	head_.setTexture(headTexture_);
	head_.setOrigin(SnakeNode::NodeRadius, SnakeNode::NodeRadius);
	head_.setPosition(Game::Width / 2, Game::Height / 2);
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.emplace_back(sf::Vector2f(Game::Width / 2,
										 Game::Height / 2 - SnakeNode::MoveDistance * i));
	}
	nodes_.front().setCircleColor(sf::Color::Transparent);
}
void Snake::updateDirection(const sf::Vector2f &mousePos)
{
	static const float maxdelta = 30.f;
	float origin = direction_.asAngle();
	direction_.update(nodes_.front().getPosition(), mousePos);
	float delta = direction_.asAngle() - origin;

	// limit angle variation to 30 degrees
	if (delta >= 0.f)
	{
		if (delta <= maxdelta && delta > 360.f - maxdelta)
		{
			direction_.update(origin);
		}
		else if (delta > maxdelta && delta <= 180.f)
		{
			direction_.update(origin + maxdelta);
		}
		else if (delta > 180.f && delta < 360.f - maxdelta)
		{
			direction_.update(origin - maxdelta);
		}
	}
	else
	{
		if (delta >= -maxdelta && delta < maxdelta - 360.f)
		{
			direction_.update(origin);
		}
		else if (delta < -maxdelta && delta >= -180.f)
		{
			direction_.update(origin - maxdelta);
		}
		else if (delta < -180.f && delta > maxdelta - 360.f)
		{
			direction_.update(origin + maxdelta);
		}
	}
}
void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto itr = nodes_.rbegin(); itr != nodes_.rend(); ++itr)
		target.draw(*itr);
	target.draw(head_);
}