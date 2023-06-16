#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	font_.loadFromFile("Fonts/REEJI-TaikoRiskGB-Flash.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!"
															 "\n\nPress [SPACE] to retry"
															 "\n\nPress [ESC] to quit");

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
					textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true)
	{
		sf::sleep(sf::milliseconds(10));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true)
		{
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true)
				sf::sleep(sf::milliseconds(10));

			sf::sleep(sf::milliseconds(20));

			Game::Screen = std::make_shared<OptionScreen>();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}
