#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

#define FRUIT_MAX 10
using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
	Fruit::initTexture();
}
GameScreen::GameScreen(const Option& option, sf::RenderWindow &window) : snake_()
{
	world_.setGridColor(option.gridColor);
	world_.setWorldColor(option.worldColor);
	window.setFramerateLimit(option.frameRate);
	Fruit::initTexture();
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	static int score{0};
	if (fruit_.size() < FRUIT_MAX)
		generateFruit();

	snake_.update(delta);
	if (snake_.checkFruitCollisions(fruit_) == true)
	{
		score_ += 5;
	}
	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(score_);
}

void GameScreen::render(sf::RenderWindow &window)
{
	window.draw(world_);
	window.draw(snake_);
	for (const auto& fruit : fruit_)
		window.draw(fruit);
}
sf::Vector2f generatePos(Snake &snake_)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::NodeRadius * 2);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::NodeRadius * 2);
	sf::FloatRect bound;
	// assure there's no collision between fruit and snake
	do
	{
		bound = sf::FloatRect(xDistribution(engine), yDistribution(engine), Fruit::Radius * 2, Fruit::Radius * 2);
	} while(snake_.checkBodyBlock(bound) == true);
	return sf::Vector2f(bound.left, bound.top);
}
sf::Color generateColor()
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_real_distribution<float> colorDistribution(0.f, 1.f);
	float r = colorDistribution(engine);
	if(r >= 0.f && r < 0.125f)
		return sf::Color::Black;
	else if(r >=0.125f && r < 0.25f)
		return Color::Brown;
	else if(r >= 0.25f && r < 0.5f)
		return sf::Color::Red;
	else if(r >= 0.5f && r < 0.75f)
		return sf::Color::Blue;
	else if(r >= 0.75f && r < 1.f)
		return sf::Color::Green; 
	
	// if the random number is out of range, return transparent
	return sf::Color::Transparent;
}
void GameScreen::generateFruit()
{
	// note : without the :: , the compiler won't recognize the function
	fruit_.emplace_back(::generatePos(snake_), ::generateColor());
}
