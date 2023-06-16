#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "World.h"
#include "OptionScreen.h"

namespace sfSnake
{
	class GameScreen : public Screen
	{
	public:
		GameScreen();
		GameScreen(const Option &option, sf::RenderWindow &window);

		void handleInput(sf::RenderWindow &window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow &window) override;
		void generateFruit();

	private:
		Snake snake_;
		std::vector<Fruit> fruit_;
		World world_;
		size_t score_{0};
	};
	static sf::Vector2f generatePos(Snake &snake_);
	static sf::Color generateColor();
}

#endif