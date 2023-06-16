#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>

#include "Screen.h"

namespace sfSnake
{
	class Game
	{
	public:
		Game();

		void run();

		void handleInput();
		void update(sf::Time delta);
		void render();

		// slightly adjust width and height to make the game look better
		static const int Width = 960;
		static const int Height = 540;

		static std::shared_ptr<Screen> Screen;

	private:
		sf::RenderWindow window_;
		sf::Music bgMusic_;

		static sf::Time DeltaTime;
	};
}

#endif