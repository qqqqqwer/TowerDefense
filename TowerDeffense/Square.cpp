#include "Square.h"
#include "Constants.h"
#include <iostream>


void Square::setHoverTower(sf::Sprite & sprite)
{
	this->hoverSprite = sprite;
	sprite.setPosition((sf::Vector2f)position);
}

void Square::LoadImage(sf::Texture & texture) {
	sprite.setTexture(texture);
}

void Square::Init(int x, int y, sf::Texture & texture, Purpose pur) {
	position = sf::Vector2i((int)x * SPRITE_DIMENSION, (int)y * SPRITE_DIMENSION);
	LoadImage(texture);
	sprite.setPosition((sf::Vector2f)position);
	p = pur;
}

void Square::DrawSquare(sf::RenderWindow & window) {
	window.draw(sprite);
	window.draw(hoverSprite);
}

sf::Vector2i Square::getPosition() {
	return position;
}

void Square::SetColor(sf::Color color)
{
	sprite.setColor(color);
}

sf::Sprite Square::getSprite()
{
	return sprite;
}

void Square::setSprite(sf::Sprite & sprt)
{
	this->sprite = sprt;
	sprite.setPosition((sf::Vector2f)position);
}

void Square::LoadHoverTowerImage(sf::Texture & texture)
{
	this->hoverSprite.setTexture(texture);
	hoverSprite.setPosition((sf::Vector2f)position);
}

void Square::setTowerTransperent(bool trans)
{
	sf::Color color = this->hoverSprite.getColor();

	if (trans) 
		color.a = 255;
	else 
		color.a = 0;

	hoverSprite.setColor(color);
}

void Square::setHoverTowerSpriteColor(sf::Color color)
{
	this->hoverSprite.setColor(color);
}

Purpose Square::getPurpose()
{
	return p;
}
