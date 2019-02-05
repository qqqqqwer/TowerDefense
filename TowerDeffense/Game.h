#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"
#include <fstream>
#include <iostream>
#include "Constants.h"
#include "Enemy.h"
#include <vector>
#include "Timer.h"

class Game {
private:
	Square grid[BOARD_WIDTH][BOARD_HEIGHT];
	int levelNumber;
	int waveSize;
	int deadEnemies;
	int ens;
	int en;
	int waveNumber; 
	bool isTowerSelected;
	bool isWaveSpawned; 
	int damageModifier;
	std::string selectedTower;
	Enemy* enemies;
	sf::Clock enemyClock;
	sf::Clock spawnClock;
	sf::Clock waveClock;
	sf::Text timerText;
	sf::Font timerTextFont;
	sf::Texture nextWaveButtonTexture;
	sf::Sprite nextWaveButton;
	sf::Text damageText;
	sf::Text rangeText;
	sf::Text speedText;

	sf::Texture backgroundTexture;
	sf::Sprite background;
	
	sf::Texture menuTexture;
	sf::Sprite menu;

	sf::CircleShape towersRange;

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

	sf::RectangleShape PauseMenu; 
	bool _isGamePaused; 
	sf::Clock pauseClock;
	sf::Time pauseTime;

	void LoadMap();
	void SetUpUI();
	void LoadResources();
	void DamageEnemies();
	void SpawnNextWave(int number);
	sf::Sprite sellButton; 
	sf::Sprite upgradeButton;
	sf::Texture sellButtonTexture;
	sf::Texture upgradeButtonTexture;
	int money; 
	sf::Text moneyText;

	sf::Vector2i selectedGridTowerCoordaintes;

public:
	void Initialize();
	void DrawLevel(sf::RenderWindow & window);
	void CheckMouseClicks(sf::Vector2i mouse);
	void CheckMousePosition(sf::Vector2i mouse);
	void UpdateGame();
	void UnselectTower(sf::Vector2i mouse);
	void ResumeGame();
	bool isGamePaused(); 
};