#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include <string>

using namespace sfSnake;

const float Fruit::Radius = 10.f;
const sf::Color Color::Brown = sf::Color(210, 180, 140);
const std::vector<sf::Vector2f> Fruit::Scaler = {
	{sf::Vector2f(1.f / 10.f, 1.f / 10.f)}, // Red
	{sf::Vector2f(1.f / 4.f, 1.f / 4.f)},	// Blue
	{sf::Vector2f(1.f / 8.f, 1.f / 8.f)},	// Greem
	{sf::Vector2f(1.f / 6.f, 1.f / 6.f)},	// Brown
	{sf::Vector2f(1.f / 8.f, 1.f / 8.f)}	// Black
};
const std::vector<sf::IntRect> Fruit::TextureRect = {
	{sf::IntRect(0, 0, 200, 200)},	 // Red
	{sf::IntRect(0, 125, 80, 80)},	 // Blue
	{sf::IntRect(5, 40, 200, 200)},	 // Green
	{sf::IntRect(10, 10, 140, 140)}, // Brown
	{sf::IntRect(20, 10, 180, 180)}, // Black
};
const std::vector<std::string> textureSource{
	"Textures/Fruit/Red.png",
	"Textures/Fruit/Blue.png",
	"Textures/Fruit/Green.png",
	"Textures/Fruit/Brown.png",
	"Textures/Fruit/Black.png"};
std::vector<sf::Texture> Fruit::Texture;

Fruit::Fruit(const sf::Vector2f position, const sf::Color &color)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(color);

	if (color == sf::Color::Red)
	{
		sprite_.setTexture(Texture[0]);
		sprite_.setScale(Scaler[0]);
	}
	else if (color == sf::Color::Blue)
	{
		sprite_.setTexture(Texture[1]);
		sprite_.setScale(Scaler[1]);
	}
	else if (color == sf::Color::Green)
	{
		sprite_.setTexture(Texture[2]);
		sprite_.setScale(Scaler[2]);
	}
	else if (color == Color::Brown)
	{
		sprite_.setTexture(Texture[3]);
		sprite_.setScale(Scaler[3]);
	}
	else if (color == sf::Color::Black)
	{
		sprite_.setTexture(Texture[4]);
		sprite_.setScale(Scaler[4]);
	}
	sprite_.setPosition(position);
}
void Fruit::initTexture()
{
	Texture.reserve(5);
	for (int i = 0; i < 5; ++i)
	{
		Texture.emplace_back();
		Texture[i].loadFromFile(textureSource[i], TextureRect[i]);
	}
}

int Fruit::bonusLength() const
{
	sf::Color color = shape_.getFillColor();
	if (color == sf::Color::Black)
		return 0;
	else if (color == sf::Color::Red)
		return 3;
	else if (color == sf::Color::Blue)
		return 2;
	else if (color == sf::Color::Green)
		return 1;
	else if (color == Color::Brown)
		return 0;
	else
		return 0;
}
