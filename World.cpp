#include <SFML/Graphics.hpp>
#include "World.h"
#include "Game.h"

using namespace sfSnake;
World::World(const sf::Color &worldColor, const sf::Color &gridColor)
{
    world_.setFillColor(worldColor);
    world_.setSize(sf::Vector2f(Game::Width, Game::Height));
    grid_.setPrimitiveType(sf::Lines);
    const int xnumber = Game::Width / gap - 1;
    const int ynumber = Game::Height / gap - 1;
    grid_.resize(2 * xnumber + 2 * ynumber);
    sf::Vertex *line = &(grid_[0]);
    for (int i = 0; i < xnumber; ++i)
    {
        line[2 * i].position = sf::Vector2f(gap * (i + 1), 0);
        line[2 * i].color = gridColor;
        line[2 * i + 1].position = sf::Vector2f(gap * (i + 1), Game::Height);
        line[2 * i + 1].color = gridColor;
    }
    line = &(grid_[2 * xnumber]);
    for (int i = 0; i < ynumber; ++i)
    {
        line[2 * i].position = sf::Vector2f(0, gap * (i + 1));
        line[2 * i].color = gridColor;
        line[2 * i + 1].position = sf::Vector2f(Game::Width, gap * (i + 1));
        line[2 * i + 1].color = gridColor;
    }
}

void World::setGridColor(const sf::Color &gridColor)
{
    const int xnumber = Game::Width / gap - 1;
    const int ynumber = Game::Height / gap - 1;
    sf::Vertex *line = &(grid_[0]);
    for (int i = 0; i < xnumber; ++i)
    {
        line[2 * i].color = gridColor;
        line[2 * i + 1].color = gridColor;
    }
    line = &(grid_[2 * xnumber]);
    for (int i = 0; i < ynumber; ++i)
    {
        line[2 * i].color = gridColor;
        line[2 * i + 1].color = gridColor;
    }
}
