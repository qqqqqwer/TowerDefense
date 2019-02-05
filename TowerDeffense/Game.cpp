#pragma once
#include "Game.h"
#include <iomanip>
#include <thread>
#include <math.h>

void Game::LoadMap() {
	emptyTexture.create(SPRITE_DIMENSION, SPRITE_DIMENSION);
	pathTexture.loadFromFile("path.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));
	tower1Texture.loadFromFile("tower1.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));
	towerPlacementTexture.loadFromFile("TowerPlacement.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));

	std::ifstream levelFile("Game.txt");
	std::cout << "level" + std::to_string(levelNumber) + ".txt" << "\n";

	backgroundTexture.loadFromFile("Game.png", sf::IntRect(0, 0, PLAYFIELD_WIDTH, PLAYFIELD_HEIGHT));
	background.setTexture(backgroundTexture);

	menuTexture.loadFromFile("InGameMenu.png");
	menu.setTexture(menuTexture);
	menu.setPosition(0, 720);

	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {

			int s;
			levelFile >> s;
			std::cout << s << " ";

			if (s == 0)
				grid[x][y].Init(x, y, emptyTexture, constants::Purpose::Ambient);

			if (s == 1)
				grid[x][y].Init(x, y, pathTexture, constants::Purpose::Path);

			if (s == 2)
				grid[x][y].Init(x, y, towerPlacementTexture, constants::Purpose::BuildingPlace);

			if (s == 3)
				grid[x][y].Init(x, y, pathTexture, constants::Purpose::End);

		}
		std::cout << "\n";
	}

	levelFile.close();
}

void Game::SetUpUI()
{
	//next wave timer text
	this->timerTextFont.loadFromFile("arial.ttf");
	this->timerText.setFont(this->timerTextFont);
	this->timerText.setString("10");
	this->timerText.setCharacterSize(24);
	this->timerText.setFillColor(sf::Color::Red);
	this->timerText.setStyle(sf::Text::Regular);
	this->timerText.setPosition(950, 760);

	//next wave button
	this->nextWaveButtonTexture.loadFromFile("new wave button.png");
	this->nextWaveButton.setTexture(nextWaveButtonTexture);
	this->nextWaveButton.setPosition(988, 762);

	this->damageText.setFont(timerTextFont);
	this->damageText.setCharacterSize(16);
	this->damageText.setFillColor(sf::Color::White);
	this->damageText.setStyle(sf::Text::Regular);
	this->damageText.setPosition(300, 750);
	this->damageText.setString("");

	this->rangeText.setFont(timerTextFont);
	this->rangeText.setCharacterSize(16);
	this->rangeText.setFillColor(sf::Color::White);
	this->rangeText.setStyle(sf::Text::Regular);
	this->rangeText.setPosition(450, 750);
	this->rangeText.setString("");

	this->speedText.setFont(timerTextFont);
	this->speedText.setCharacterSize(16);
	this->speedText.setFillColor(sf::Color::White);
	this->speedText.setStyle(sf::Text::Regular);
	this->speedText.setPosition(600, 750);
	this->speedText.setString("");

	this->moneyText.setFont(timerTextFont);
	this->moneyText.setCharacterSize(20);
	this->moneyText.setFillColor(sf::Color::Yellow);
	this->moneyText.setStyle(sf::Text::Regular);
	this->moneyText.setPosition(800, 821);
	this->moneyText.setString("");

	this->sellButtonTexture.loadFromFile("sell button.png");
	this->sellButton.setTexture(sellButtonTexture);
	this->sellButton.setPosition(313, 842);
	this->sellButton.setColor(sf::Color::Red);
	this->upgradeButtonTexture.loadFromFile("upgrade button.png");
	this->upgradeButton.setTexture(upgradeButtonTexture);
	this->upgradeButton.setPosition(524, 842);
	this->upgradeButton.setColor(sf::Color::Red);


	//pause menu
	PauseMenu.setFillColor(sf::Color(0, 0, 255, 160));
	PauseMenu.setSize(sf::Vector2f(PAUSE_MENU_WIDTH, PAUSE_MENU_HEIGHT));
	PauseMenu.setPosition(PLAYFIELD_WIDTH / 2 - (PAUSE_MENU_WIDTH / 2), PLAYFIELD_HEIGHT / 2 - (PAUSE_MENU_HEIGHT / 2));
}

void Game::Initialize() {
	this->deadEnemies = 0;
	this->waveSize = STARTING_WAVE_SIZE;
	this->ens = 0;
	this->en = 0;
	this->isTowerSelected = false;
	this->isWaveSpawned = false;
	this->enemyClock.restart();
	this->spawnClock.restart();
	this->waveClock.restart();
	this->_isGamePaused = false;
	this->waveNumber = 0;
	this->damageModifier = 0;
	this->money = STARTING_MONEY;
	SetUpUI();
	LoadMap();

	towersRange.setFillColor(sf::Color(0, 130, 0, 120));
}

void Game::LoadResources() {

	this->tower1Texture.loadFromFile("tower1.png");
	this->tower2Texture.loadFromFile("tower2.png");
	this->tower3Texture.loadFromFile("tower4.png");
	this->tower4Texture.loadFromFile("tower3.png");
}

void Game::DamageEnemies() {
	
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			if (grid[x][y].getPurpose() == constants::Purpose::Tower) {

				int maxX = 0;
				int maxY = 0;
				int index = -1;
				double D;

				sf::Vector2i towerPos = grid[x][y].getPosition();
				towerPos.x += (SPRITE_DIMENSION / 2);
				towerPos.y += (SPRITE_DIMENSION / 2);
				for (int i = 0; i < waveSize; i++) {
					D = sqrt(pow((towerPos.x - (enemies[i].getPosition().x + (SPRITE_DIMENSION / 2))), 2) + pow((towerPos.y - (enemies[i].getPosition().y + (SPRITE_DIMENSION / 2))), 2));
					if (D <= std::get<1>(grid[x][y].getTowerStats())) {

						if (maxX < enemies[i].getPosition().x) {
							maxX = enemies[i].getPosition().x;
							index = i;
						}
						else if (maxX == enemies[i].getPosition().x) {

							if (maxY < enemies[i].getPosition().y) {
								maxY = enemies[i].getPosition().y;
								index = i;
							}
						}
					}
				}

				if (index > -1) {
					int damage = std::get<0>(grid[x][y].getTowerStats());
					int speed = std::get<2>(grid[x][y].getTowerStats());
					if (grid[x][y].fireRateClock.getElapsedTime().asSeconds() >= speed) {
						enemies[index].TakeDamage(damage, money);
						grid[x][y].fireRateClock.restart();

						if (enemies[index].isDead()) {
							money += (rand() % 50 + 100);
							deadEnemies++;
						}
					}
					
				}

			}
		}
	}

}

void Game::SpawnNextWave(int number)
{
	srand((unsigned int)NULL);

	this->waveNumber++;
	if (waveNumber % 4 == 0)
		damageModifier += rand() % 35;

	pauseTime = sf::seconds(0);

	this->isWaveSpawned = true;
	enemies = new Enemy[number];

	srand((unsigned int)time(NULL));
	for (int i = 0; i < number; i++)
		enemies[i].Init(rand() % 2, 50 + this->damageModifier, rand() % 2 + 1);
}

void Game::DrawLevel(sf::RenderWindow & window) {

	window.draw(background);
	window.draw(menu);

	for (int y = 0; y < 15; y++)
		for (int x = 0; x < 25; x++)
			grid[x][y].DrawSquare(window);

	if (this->isWaveSpawned)
		for (int i = 0; i < waveSize; i++) {
			window.draw(enemies[i].getSprite());
			window.draw(enemies[i].getHPBar() );
		}

	window.draw(towersRange);
	
	//draw UI elements
	window.draw(this->timerText);
	window.draw(this->nextWaveButton);
	window.draw(this->damageText);
	window.draw(this->rangeText);
	window.draw(this->speedText);
	window.draw(this->sellButton);
	window.draw(this->upgradeButton);
	window.draw(this->moneyText);

	if (_isGamePaused)
		window.draw(PauseMenu);
}

void Game::CheckMouseClicks(sf::Vector2i mouse) {
	if (!_isGamePaused) {
		if (mouse.y <= 720 && mouse.y >= 0) {
			int x = mouse.x / SPRITE_DIMENSION;
			int y = mouse.y / SPRITE_DIMENSION;

			if (isTowerSelected && (grid[x][y].getPurpose() == constants::Purpose::BuildingPlace)) {
				money += -100;
				if (this->selectedTower == "tower1") {
					tower1Texture.loadFromFile("tower1.png");
					grid[x][y].PlaceTower(tower1Texture, sf::Vector2i(x, y) * SPRITE_DIMENSION, 1);
				}

				if (this->selectedTower == "tower2") {
					tower2Texture.loadFromFile("tower2.png");
					grid[x][y].PlaceTower(tower2Texture, sf::Vector2i(x, y) * SPRITE_DIMENSION, 2);
				}

				if (this->selectedTower == "tower3") {
					tower3Texture.loadFromFile("tower3.png");
					grid[x][y].PlaceTower(tower3Texture, sf::Vector2i(x, y) * SPRITE_DIMENSION, 3);
				}

				if (this->selectedTower == "tower4") {
					tower4Texture.loadFromFile("tower4.png");
					grid[x][y].PlaceTower(tower4Texture, sf::Vector2i(x, y) * SPRITE_DIMENSION, 4);
				}

				if (money < 100) {
					UnselectTower(mouse);
				}
			}

			if (!isTowerSelected && (grid[x][y].getPurpose() == constants::Purpose::Tower))
			{
				std::tuple<int, int, int> stats = grid[x][y].getTowerStats();
				std::cout << std::get<0>(stats) << " " << std::get<1>(stats) << " " << std::get<2>(stats) << "\n";
				this->damageText.setString("atk: " + std::to_string(std::get<0>(stats)));
				this->rangeText.setString("range: " + std::to_string(std::get<1>(stats)));
				this->speedText.setString("speed: " + std::to_string(std::get<2>(stats)));
				towersRange.setRadius((float)std::get<1>(stats));
				towersRange.setOrigin(towersRange.getRadius(), towersRange.getRadius());
				towersRange.setPosition((float)x * SPRITE_DIMENSION + SPRITE_DIMENSION / 2, (float)y * SPRITE_DIMENSION + SPRITE_DIMENSION / 2);
				this->sellButton.setColor(sf::Color::Transparent);
				this->upgradeButton.setColor(sf::Color::Transparent);

				selectedGridTowerCoordaintes.x = x;
				selectedGridTowerCoordaintes.y = y;
				std::cout << x << " " << y << "\n";
			}

		}

		//check tower buttons
		if (money >= 100) {

			//top left
			if (mouse.x >= 56 && mouse.y >= 760 && mouse.x <= 56 + 50 && mouse.y <= 760 + 50) {
				hoverTower.loadFromFile("tower2.png");
				isTowerSelected = true;
				this->selectedTower = "tower2";
			}

			//top right
			if (mouse.x >= 118 && mouse.y >= 760 && mouse.x <= 118 + 50 && mouse.y <= 760 + 50) {
				hoverTower.loadFromFile("tower3.png");
				isTowerSelected = true;
				this->selectedTower = "tower3";
			}

			//bottom left
			if (mouse.x >= 56 && mouse.y >= 816 && mouse.x <= 56 + 50 && mouse.y <= 816 + 50) {
				hoverTower.loadFromFile("tower1.png");
				isTowerSelected = true;
				this->selectedTower = "tower1";
			}

			//bottom right
			if (mouse.x >= 118 && mouse.y >= 816 && mouse.x <= 118 + 50 && mouse.y <= 816 + 50) {
				hoverTower.loadFromFile("tower4.png");
				isTowerSelected = true;
				this->selectedTower = "tower4";
			}
		}

		//this->sellButton.setPosition(313, 842); 100 x 30
		//this->upgradeButton.setPosition(524, 842); 100 x 30 
		

		if (sellButton.getColor() == sf::Color::Transparent && upgradeButton.getColor() == sf::Color::Transparent) {
			//check sell button
			if (mouse.x >= 313 && mouse.y >= 842 && mouse.x <= 313 + 100 && mouse.y <= 842 + 30) {
				
				money += grid[selectedGridTowerCoordaintes.x][selectedGridTowerCoordaintes.y].Sell();

			}

			//check upgrade button
			if (mouse.x >= 524 && mouse.y >= 814 && mouse.x <= 524 + 100 && mouse.y <= 842 + 30) {
				
				if (money >= grid[selectedGridTowerCoordaintes.x][selectedGridTowerCoordaintes.y].getUpgradePrice()) {
					grid[selectedGridTowerCoordaintes.x][selectedGridTowerCoordaintes.y].Upgrade();
					money -= grid[selectedGridTowerCoordaintes.x][selectedGridTowerCoordaintes.y].getUpgradePrice();
				}

			}
		}
		

		//check menu button
		if (mouse.x >= 1000 && mouse.y >= 821 && mouse.x <= 1000 + 140 && mouse.y <= 821 + 30) {

			//if game is being unpaused then get elapsed time. If game is being paused restart the clock
			pauseClock.restart();
			_isGamePaused = true;
		}

		//check next wave button
		if (mouse.x >= 988 && mouse.y >= 762 && mouse.x <= 988 + 160 && mouse.y <= 762 + 28) {

			if (!this->isWaveSpawned) {
				this->timerText.setString("");
				this->SpawnNextWave(this->waveSize);
			}
		}
	}
}

void Game::CheckMousePosition(sf::Vector2i mouse) {

	sf::Texture empty;
	
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			if (isTowerSelected) {
				grid[x][y].LoadHoverTowerImage(hoverTower);

				if ((mouse.x > grid[x][y].getPosition().x && mouse.x < grid[x][y].getPosition().x + SPRITE_DIMENSION) && (mouse.y > grid[x][y].getPosition().y && mouse.y < grid[x][y].getPosition().y + SPRITE_DIMENSION)) {
					grid[x][y].setTowerTransperent(true);

					if (grid[x][y].getPurpose() == constants::Purpose::BuildingPlace && money >= 100)
						grid[x][y].setHoverTowerSpriteColor(sf::Color::Green);
					else
						grid[x][y].setHoverTowerSpriteColor(sf::Color::Red);
				}
				else
					grid[x][y].setTowerTransperent(false);
			}
		}
	}
}

std::string TimerNumberToString(float number) {

	if (number <= 0)
		return "";

	std::string num = std::to_string(number);
	std::string newNum;
	newNum += num[0];
	newNum += num[1];
	newNum += num[2];
	
	return newNum;
}

void Game::UpdateGame()
{
	moneyText.setString(std::to_string(this->money));

	if (isTowerSelected) {
		int atk;
		int spd;
		int rng;
		
		if (selectedTower == "tower1") {
			atk = 10;
			rng = 10;
			spd = 10;
		}
		else if (selectedTower == "tower2") {
			atk = 5;
			rng = 12;
			spd = 13;
		}
		else if (selectedTower == "tower3") {
			atk = 18;
			rng = 8;
			spd = 4;
		}
		else if (selectedTower == "tower4") {
			atk = 3;
			rng = 15;
			spd = 12;
		}
		this->damageText.setString("atk: " + std::to_string(atk));
		this->speedText.setString("speed: " + std::to_string(spd));
		this->rangeText.setString("range: " + std::to_string(rng));
	}

	if (!_isGamePaused) {
		sf::Color color = this->nextWaveButton.getColor();
		if (!this->isWaveSpawned) {
			color.g = 255;
			float timeRemaining = sf::seconds(WAVE_TIME).asSeconds() - this->waveClock.getElapsedTime().asSeconds() + pauseTime.asSeconds();
			this->timerText.setString(TimerNumberToString(timeRemaining));
			
			if (timeRemaining <= 0) {
				SpawnNextWave(this->waveSize);
			}
		}
		else {
			color.g = 0;
			if (this->waveSize != this->deadEnemies) {
				//Spawning
				if (this->spawnClock.getElapsedTime().asSeconds() >= 2) {
					ens = ens % waveSize;

					//if enemy is uninitialized
					if (!enemies[ens].isVisible() && !enemies[ens].isDead()) {
						//initialize
						enemies[ens].setVisible(true);
						enemies[ens].setPosition(sf::Vector2i(0, 4 * 48));
					}

					enemies[ens].Move(grid);

					ens++;
					spawnClock.restart();
				}

				//Update enemy position (and maybe something else)
				if (this->enemyClock.getElapsedTime().asMilliseconds() >= FRAMERATE) {
					for (int i = 0; i < this->waveSize; i++) {
						enemies[i].Move(grid);

						int enemyX = enemies[i].getPosition().x / SPRITE_DIMENSION;
						int enemyY = enemies[i].getPosition().y / SPRITE_DIMENSION;

						if (this->grid[enemyX][enemyY].getPurpose() == constants::Purpose::End) {
							this->enemies[i].Die();
							this->deadEnemies++;
						}
					}
					this->enemyClock.restart();
				}
				DamageEnemies();
			}
			//if there are no enemies
			else {

				this->waveSize += rand() % 2 + rand() % 2;
				this->waveClock.restart();
				this->isWaveSpawned = false;
				delete[] this->enemies;
				this->deadEnemies = 0;
			}
		}
		this->nextWaveButton.setColor(color);
	}
}

void Game::UnselectTower(sf::Vector2i mouse)
{
	int x = mouse.x / SPRITE_DIMENSION;
	int y = mouse.y / SPRITE_DIMENSION;
	this->damageText.setString("");
	this->speedText.setString("");
	this->rangeText.setString("");
	this->towersRange.setRadius(0);
	this->sellButton.setColor(sf::Color::Red);
	this->upgradeButton.setColor(sf::Color::Red);

	grid[x][y].setHoverTowerVisible(false);
	this->isTowerSelected = false;
}

void Game::ResumeGame() {
	pauseTime += pauseClock.getElapsedTime();
	_isGamePaused = false;
}

bool Game::isGamePaused() {
	return _isGamePaused;
}