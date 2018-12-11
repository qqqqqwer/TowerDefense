#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include <fstream>
#include <iostream>
#include "Constants.h"
class Level {

private:
	Square grid[BOARD_WIDTH][BOARD_HEIGHT];
	int levelNumber;
	bool isTowerSelected;

	sf::Texture backgroundTexture;
	sf::Sprite background;
	
	sf::Texture menuTexture;
	sf::Sprite menu;

	sf::Texture emptyTexture;
	sf::Texture towerPlacementTexture;
	sf::Texture tower1Texture;
	sf::Texture tower2Texture;
	sf::Texture tower3Texture;
	sf::Texture tower4Texture;
	sf::Texture enemy1Texture;
	sf::Texture enemy2Texture;
	sf::Texture pathTexture;

	sf::Sprite tower1;
	sf::Sprite tower2;
	sf::Sprite tower3;
	sf::Sprite tower4;
	sf::Texture hoverTower;
	std::vector<sf::RectangleShape> buttons;

	void LoadMap();
	void LoadResources();
	void SpawnNextWave();

public:
	void Initialize(int levelNumber);
	void DrawLevel(sf::RenderWindow & window);
	void CheckMouseClicks(sf::Vector2i mouse);
	void CheckMousePosition(sf::Vector2i mouse);
	void AddRectangleShape(float  x, float y, float width, float height);
	void UnselectTower();
	bool isInsideASquare(int x, int y, int mx, int my);
};