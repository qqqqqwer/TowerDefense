#include "Enemy.h"
#include <iostream>

void Enemy::Init(int r) {
	r ==  0 ? this->texture.loadFromFile("monster1.png") : this->texture.loadFromFile("monster2.png");
	this->sprite.setTexture(this->texture);
	setVisible(false);

	this->direction = sf::Vector2i(0, 0);
	this->dead = false;
}

Enemy::~Enemy()
{

}

void Enemy::LoadImage(sf::Texture & texture)
{
	
}

sf::Sprite Enemy::getSprite()
{
	return this->sprite;
}

sf::Vector2i Enemy::getPosition()
{
	return this->position;
}

void Enemy::setPosition(sf::Vector2i position)
{
	this->position = position;
	this->sprite.setPosition((sf::Vector2f)position);
}

void Enemy::setVisible(bool invis)
{
	sf::Color color = this->sprite.getColor();
	invis ? color.a = 255 : color.a = 0;
	this->sprite.setColor(color);
}

bool Enemy::isVisible()
{
	bool vis;
	this->sprite.getColor().a == 0 ? vis = false : vis = true;
	return vis;
}

void Enemy::Move(Square grid[][BOARD_HEIGHT])
{
	// 1. Find the square the monster is on
	// 2. Look at nearby squares
	// 3. Move to the nearest square that is path

	if (!dead) {

		int x = getPosition().x / SPRITE_DIMENSION;
		int y = getPosition().y / SPRITE_DIMENSION;


		if (grid[x + 1][y].getPurpose() == Purpose::Path)
			this->direction = sf::Vector2i(1, 0);
		if (grid[x][y + 1].getPurpose() == Purpose::Path)
			this->direction = sf::Vector2i(0, 1);

		/*

			if you'll have time another way to do the movement is to place
			every path block into an array and have the monster follow that path
			instead of checking for the nearest path block everytime

		*/


		this->position += this->direction;
		this->sprite.setPosition((sf::Vector2f)position);
	}
	
}

void Enemy::Die()
{
	this->dead = true;
	this->setPosition(sf::Vector2i(2, 0) * SPRITE_DIMENSION);
	this->setVisible(false);
}

bool Enemy::isDead()
{
	return this->dead;
}
