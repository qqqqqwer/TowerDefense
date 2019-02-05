#include "Enemy.h"
#include <iostream>

void Enemy::AdjustHPBar()
{
	hpBar.setSize(sf::Vector2f((float)hp / fullHP * 100 * 0.5f, (float)5));
}

void Enemy::Init(int r, int hp, int speed) {
	r ==  0 ? this->texture.loadFromFile("monster1.png") : this->texture.loadFromFile("monster2.png");
	this->sprite.setTexture(this->texture);
	setVisible(false);

	this->hp = hp;
	this->fullHP = hp;
	this->speed = speed;

	this->direction = sf::Vector2i(0, 0);
	this->dead = false;

	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize(sf::Vector2f(50, 5));
}

Enemy::~Enemy()
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
	this->hpBar.setPosition((float)position.x, (float)position.y + 50);
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


		if (grid[x + 1][y].getPurpose() == constants::Purpose::Path)
			this->direction = sf::Vector2i(speed, 0);
		if (grid[x][y + 1].getPurpose() == constants::Purpose::Path)
			this->direction = sf::Vector2i(0, speed);

		this->position += this->direction;
		this->setPosition(position);
	}
	else {
		hpBar.setFillColor(sf::Color::Transparent);
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

void Enemy::TakeDamage(int dmg, int & money)
{
	this->hp -= dmg;
	AdjustHPBar();
	if (hp <= 0) {
		Die();
	}
}

sf::RectangleShape Enemy::getHPBar() {
	if (this->isVisible())
		return this->hpBar;
	else
		return sf::RectangleShape();
}
