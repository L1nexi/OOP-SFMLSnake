#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    unsigned const gap{40};
    class World : public sf::Drawable, public sf::Transformable
    {
    public:
        World(const sf::Color &worldColor = sf::Color::Black, const sf::Color &gridColor = sf::Color::Transparent);
        void setWorldColor(const sf::Color &color);
        void setGridColor(const sf::Color &color);

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        sf::RectangleShape world_;
        sf::VertexArray grid_;
    };
    inline void World::setWorldColor(const sf::Color &color)
    {
        world_.setFillColor(color);
    }
    inline void World::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(world_, states);
        target.draw(grid_, states);
    }
} // namespace sfSnake

#endif