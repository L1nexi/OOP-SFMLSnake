#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
sf::Time Game::DeltaTime = sf::seconds(1.f / 10.f);
Game::Game()
	: window_(sf::VideoMode(Game::Width, Game::Height), "Snake!!")
{
	bgMusic_.openFromFile("Music/Reach for the Summit.ogg");
	bgMusic_.setLoop(true);
	bgMusic_.play();
	// use sf::Window::setFramerateLimit provided by SFML
	// to set the frame rate of the game
	window_.setFramerateLimit(20);
}

// Todo 移入run函数中
void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
		Game::Screen->handleInput(window_);
	}
}

inline void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

inline void Game::render()
{
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	// change 1:
	while (window_.isOpen())
	{
		// using sf::Window::setFramerateLimit in low FPS situation
		// using TimePerFrame
		handleInput();
		update(DeltaTime);
		render();
	}
}