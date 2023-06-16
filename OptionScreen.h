#ifndef OPTIONSCREEN_H
#define OPTIONSCREEN_H

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Fruit.h"

namespace sfSnake
{
    // for option selection

    struct Option
    {
        sf::Color worldColor{sf::Color::Black};
        sf::Color gridColor{Color::Brown};
        size_t frameRate{10};
    };
    class OptionScreen : public Screen
    {
    public:
        OptionScreen();
        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;
        const Option &getOption() const;
        void setWorldColor(const sf::Color &color);
        void setGridColor(const sf::Color &color);
        void setFrame(const size_t &frame);

    private:
        sf::Text background_;
        sf::Text gridColor_;
        sf::Text difficulty_;
        sf::Text start_;
        sf::Font font_;
        Option option_;
    };
    inline const Option &OptionScreen::getOption() const
    {
        return option_;
    }
    inline void OptionScreen::setWorldColor(const sf::Color &color)
    {
        option_.worldColor = color;
    }
    inline void OptionScreen::setGridColor(const sf::Color &color)
    {
        option_.gridColor = color;
    }
    inline void OptionScreen::setFrame(const size_t &frame)
    {
        option_.frameRate = frame;
    }
} // namespace sfSnake

#endif