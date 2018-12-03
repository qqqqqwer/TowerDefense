#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include <fstream>
#include <iostream>
class Level {

private:
	Square grid[BOARD_WIDTH][BOARD_HEIGHT];
	int levelNumber;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture emptyTexture;
	sf::Texture towerPlacementTexture;
	sf::Texture tower1Texture;
	sf::Texture tower2Texture;
	sf::Texture tower3Texture;
	sf::Texture enemy1Texture;
	sf::Texture enemy2Texture;
	sf::Texture pathTexture;

	std::vector<sf::RectangleShape> buttons;

	void LoadMap();

public:
	void Initialize(int levelNumber);
	void DrawLevel(sf::RenderWindow & window);
	void CheckMouseClicks(sf::Vector2i mouse);
	void AddRectangleShape(float  x, float y, float width, float height);
	void SetUpUI();
};