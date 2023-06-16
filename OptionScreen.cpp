#include "OptionScreen.h"
#include "GameScreen.h"
#include "Game.h"
#include <iostream>
#include <memory>
#define CHAR_SIZE 27

using namespace sfSnake;

OptionScreen::OptionScreen()
{
    if (font_.loadFromFile("Fonts/REEJI-TaikoRiskGB-Flash.ttf") == false)
    {
        std::cout << "Fail to load fonts.\n";
    }

    background_.setFont(font_);
    background_.setString("Choose Backgournd color\n"
                          "[W] White [E] Black [R] Brown\n");
    background_.setCharacterSize(CHAR_SIZE);
    background_.setOrigin(background_.getGlobalBounds().width / 2, background_.getGlobalBounds().height / 2);
    background_.setPosition(Game::Width / 2, Game::Height * 0.2);
    background_.setFillColor(sf::Color::Black);
    background_.setOutlineColor(sf::Color::White);
    background_.setOutlineThickness(1.f);

    gridColor_.setFont(font_);
    gridColor_.setString("Choose Grid color\n"
                         "[A] White [S] Black [D] Brown [F] None");
    gridColor_.setFillColor(Color::Brown);
    gridColor_.setOutlineColor(sf::Color::White);
    gridColor_.setCharacterSize(CHAR_SIZE);
    gridColor_.setOutlineThickness(1.f);
    gridColor_.setOrigin(gridColor_.getGlobalBounds().width / 2, gridColor_.getGlobalBounds().height / 2);
    gridColor_.setPosition(Game::Width / 2, Game::Height * 0.4);

    difficulty_.setFont(font_);
    difficulty_.setString("Choose Difficulty\n"
                          "[Z] Worm [X] Centipede [C] Snake");
    difficulty_.setFillColor(sf::Color::White);
    difficulty_.setOutlineColor(sf::Color::White);
    difficulty_.setCharacterSize(CHAR_SIZE);
    difficulty_.setOutlineThickness(1.f);
    difficulty_.setOrigin(difficulty_.getGlobalBounds().width / 2, difficulty_.getGlobalBounds().height / 2);
    difficulty_.setPosition(Game::Width / 2, Game::Height * 0.6);

    start_.setFont(font_);
    start_.setString("Press [SPACE] to start");
    start_.setFillColor(sf::Color::White);
    start_.setOutlineColor(sf::Color::White);
    start_.setCharacterSize(CHAR_SIZE);
    start_.setOutlineThickness(1.f);
    start_.setOrigin(start_.getGlobalBounds().width / 2, start_.getGlobalBounds().height / 2);
    start_.setPosition(Game::Width / 2, Game::Height * 0.77);
}
void OptionScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Game::Screen = std::make_shared<GameScreen>(getOption(), std::ref(window));
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        setWorldColor(sf::Color::White);
        background_.setFillColor(sf::Color::White);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        setWorldColor(sf::Color::Black);
        background_.setFillColor(sf::Color::Black);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        setWorldColor(Color::Brown);
        background_.setFillColor(Color::Brown);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        setGridColor(sf::Color::White);
        gridColor_.setFillColor(sf::Color::White);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        setGridColor(sf::Color::Black);
        gridColor_.setFillColor(sf::Color::Black);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        setGridColor(Color::Brown);
        gridColor_.setFillColor(Color::Brown);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        setGridColor(sf::Color::Transparent);
        gridColor_.setFillColor(sf::Color::Transparent);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        setFrame(10);
        difficulty_.setFillColor(sf::Color::White);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        setFrame(15);
        difficulty_.setFillColor(sf::Color::Black);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        setFrame(20);
        difficulty_.setFillColor(Color::Brown);
    }
}

void OptionScreen::update(sf::Time delta)
{

}

void OptionScreen::render(sf::RenderWindow &window)
{
    window.draw(background_);
    window.draw(gridColor_);
    window.draw(difficulty_);
    window.draw(start_);
}