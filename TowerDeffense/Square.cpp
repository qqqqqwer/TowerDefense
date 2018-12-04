#include "Square.h"
#include "Constants.h"
#include <iostream>


void Square::LoadImage(sf::Texture & texture) {
	sprite.setTexture(texture);
}

void Square::Init(int x, int y, sf::Texture & texture) {
	position = sf::Vector2i((int)x * SPRITE_DIMENSION, (int)y * SPRITE_DIMENSION);
	LoadImage(texture);
	sprite.setPosition((sf::Vector2f)position);
}

void Square::DrawSquare(sf::RenderWindow & window) {
	window.draw(sprite);
}

sf::Vector2i Square::getPosition() {
	return position;
}

void Square::SetColor(sf::Color color)
{
	sprite.setColor(color);
}
