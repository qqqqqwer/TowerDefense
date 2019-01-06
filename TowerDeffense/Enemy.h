#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture texture; 
	sf::Vector2i position;
	sf::Vector2i direction;
	bool dead;

public:
	void Init(int r);
	~Enemy();
	void LoadImage(sf::Texture & texture);
	sf::Sprite getSprite();
	sf::Vector2i getPosition();
	void setPosition(sf::Vector2i position);
	void setVisible(bool invis);
	bool isVisible();
	void Move(Square grid[][BOARD_HEIGHT]);
	void Die();
	bool isDead();
};

