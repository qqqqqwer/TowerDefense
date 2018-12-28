#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include <fstream>
#include <iostream>
#include "Constants.h"
#include "Enemy.h"
#include <vector>

class Level {

private:
	Square grid[BOARD_WIDTH][BOARD_HEIGHT];
	int levelNumber;
	int waveSize;
	int ens;
	int en;
	bool isTowerSelected;
	std::string selectedTower;
	std::vector<Enemy*> enemies;
	sf::Clock enemyClock;
	sf::Clock spawnClock;

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

	sf::Texture hoverTower;
	std::vector<sf::RectangleShape> buttons;

	void LoadMap();
	void LoadResources();
	void SpawnNextWave(int number);

public:
	void Initialize(int levelNumber);
	void DrawLevel(sf::RenderWindow & window);
	void CheckMouseClicks(sf::Vector2i mouse);
	void CheckMousePosition(sf::Vector2i mouse);
	void UpdateGame();
	void PlaceTower(sf::Vector2i mouse);
	void UnselectTower(sf::Vector2i mouse);
};