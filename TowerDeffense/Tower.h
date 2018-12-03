#pragma once
#include "Square.h"
class Tower : public Square {

private:
	int range;
	int damage;
	int fireRate;
	int sellPrice;

	sf::Sprite towerSprite;
	sf::Sprite bulletSprite;
};