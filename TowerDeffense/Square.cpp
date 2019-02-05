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

void Square::Init(int x, int y, sf::Texture & texture, constants::Purpose pur) {
	position = sf::Vector2i((int)x * SPRITE_DIMENSION, (int)y * SPRITE_DIMENSION);
	LoadImage(texture);
	sprite.setPosition((sf::Vector2f)position);
	p = pur;
}

void Square::DrawSquare(sf::RenderWindow & window) {

	window.draw(sprite);

	if (p == constants::Purpose::Tower)
		window.draw(placedTower);
	
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

	this->hoverSprite.setColor(color);
}

void Square::setHoverTowerSpriteColor(sf::Color color)
{
	this->hoverSprite.setColor(color);
}

constants::Purpose Square::getPurpose()
{
	return p;
}

void Square::PlaceTower(sf::Texture & texture, sf::Vector2i pos, int type)
{
	this->p = constants::Purpose::Tower;
	this->placedTower.setTexture(texture);
	this->placedTower.setPosition((sf::Vector2f)pos);

	upgradePrice = 150;
	sellPrice = 50;

	if (type == 1) {
		damage = 10;
		range = 10 * RANGE_CONVERSION;
		fireRate = 1;
	}
	else if (type == 2) {
		damage = 15;
		range = 16 * RANGE_CONVERSION;
		fireRate = 2;
	}
	else if (type == 3) {
		damage = 18;
		range = 8 * RANGE_CONVERSION;
		fireRate = 3;
	}
	else if (type == 4) {
		damage = 13;
		range = 20 * RANGE_CONVERSION;
		fireRate = 2;
	}

}

void Square::setHoverTowerVisible(bool vis)
{
	sf::Color color = this->hoverSprite.getColor();

	if (vis)
		color.a = 255;
	else
		color.a = 0;

	hoverSprite.setColor(color);
}

std::tuple<int, int, int> Square::getTowerStats() {
	return std::make_tuple(damage, range, fireRate);
}

int Square::Sell()
{
	this->p = constants::Purpose::BuildingPlace;
	return sellPrice;
}

void Square::Upgrade()
{
	sellPrice += 50;
	upgradePrice += 100;

	damage *= 1.3;
	range *= 1.3;
}

int Square::getUpgradePrice() {
	return upgradePrice;
}