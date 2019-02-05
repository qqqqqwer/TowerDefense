#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "Constants.h"

class Enemy
{
private:
	void AdjustHPBar();
	sf::Sprite sprite;
	sf::Texture texture; 
	sf::Vector2i position;
	sf::Vector2i direction;
	sf::RectangleShape hpBar;
	bool dead;
	int hp; 
	int speed;
	int fullHP;

public:
	void Init(int r, int hp, int speed);
	~Enemy();
	sf::Sprite getSprite();
	sf::Vector2i getPosition();
	void setPosition(sf::Vector2i position);
	void setVisible(bool invis);
	bool isVisible();
	void Move(Square grid[][BOARD_HEIGHT]);
	void Die();
	bool isDead();
	void TakeDamage(int dmg, int & money);
	sf::RectangleShape getHPBar();
};