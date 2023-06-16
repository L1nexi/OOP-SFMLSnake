#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace sfSnake
{
	class Fruit : public sf::Drawable, public sf::Transformable
	{
	public:
		Fruit(const sf::Vector2f position) : Fruit(position, sf::Color::Red) {}
		Fruit(const sf::Vector2f position, const sf::Color &color);
		void setFillColor(const sf::Color &color) { shape_.setFillColor(color); }
		static void initTexture();
		int bonusLength() const;
		sf::FloatRect getBounds() const;
		static const float Radius;

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
		sf::CircleShape shape_;
		sf::Sprite sprite_;
		
		static const std::vector<sf::Vector2f> Scaler;
		static const std::vector<sf::IntRect> TextureRect;
		static std::vector<sf::Texture> Texture;
	};
	class Color : public sf::Color
	{
	public:
		static const sf::Color Brown;
	};
	inline sf::FloatRect Fruit::getBounds() const
	{
		return shape_.getGlobalBounds();
	}
	inline void Fruit::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}
}

#endif