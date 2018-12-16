#include "Level.h"
#include <thread>

void Level::LoadMap() {
	emptyTexture.create(SPRITE_DIMENSION, SPRITE_DIMENSION);
	pathTexture.loadFromFile("path.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));
	tower1Texture.loadFromFile("tower1.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));
	towerPlacementTexture.loadFromFile("TowerPlacement.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));


	std::ifstream levelFile("level" + std::to_string(levelNumber) + ".txt");
	std::cout << "level" + std::to_string(levelNumber) + ".txt" << "\n";


	backgroundTexture.loadFromFile("level" + std::to_string(levelNumber) + ".png", sf::IntRect(0, 0, PLAYFIELD_WIDTH, PLAYFIELD_HEIGHT));
	background.setTexture(backgroundTexture);

	menuTexture.loadFromFile("menu.png");
	menu.setTexture(menuTexture);
	menu.setPosition(0, 720);

	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			int s;
			levelFile >> s;

			std::cout << s << " ";

			if (s == 0)
				grid[x][y].Init(x, y, emptyTexture, Purpose::Ambient);

			if (s == 1)
				grid[x][y].Init(x, y, pathTexture, Purpose::Path);

			if (s == 2)
				grid[x][y].Init(x, y, towerPlacementTexture, Purpose::BuildingPlace);
			if (s == 3)
				grid[x][y].Init(x, y, pathTexture, Purpose::End);

		}
		std::cout << "\n";
	}



	levelFile.close();
}

void Level::Initialize(int levelNumber) {
	this->waveSize = 5;
	this->ens = 0;
	this->en = 0;
	this->levelNumber = levelNumber;
	isTowerSelected = false;
	LoadMap();
	SpawnNextWave(waveSize);
}

void Level::LoadResources() {

	tower1Texture.loadFromFile("tower1");
	tower2Texture.loadFromFile("tower2");
	tower3Texture.loadFromFile("tower3");
	tower4Texture.loadFromFile("tower4");

	tower1.setTexture(tower1Texture);
	tower2.setTexture(tower2Texture);
	tower3.setTexture(tower3Texture);
	tower4.setTexture(tower4Texture);
}

void Level::SpawnNextWave(int number)
{
	for (int i = 0; i < number; i++)
		enemies.push_back(new Enemy(rand() % 2));
}

void Level::DrawLevel(sf::RenderWindow & window) {

	window.draw(background);
	window.draw(menu);

	for (int y = 0; y < 15; y++) 
		for (int x = 0; x < 25; x++) 
			grid[x][y].DrawSquare(window);

	for (int i = 0; i < waveSize; i++)
		window.draw(enemies[i]->getSprite());
}

void Level::CheckMouseClicks(sf::Vector2i mouse) {

	//check grid clicks
	/*
	for (int y = 0; y < BOARD_HEIGHT; y++)
		for (int x = 0; x < BOARD_WIDTH; x++) {
			if (isInsideASquare(x, y, mouse.x, mouse.y)) {
				grid[x][y].SetColor(sf::Color::Green);
				std::cout << x << " " << y << "\n";
				return;
			}
		}

	*/

	if (mouse.y <= 720 && mouse.y >= 0) {
		int x = mouse.x / SPRITE_DIMENSION;
		int y = mouse.y / SPRITE_DIMENSION;

		if (isTowerSelected)
			grid[x][y].LoadPlacedTowerImage(hoverTower, sf::Vector2i(x * SPRITE_DIMENSION, y * SPRITE_DIMENSION));
	}

	//check tower buttons

	//top left
	if (mouse.x >= 56 && mouse.y >= 760 && mouse.x <= 56 + 50 && mouse.y <= 760 + 50) {
		hoverTower.loadFromFile("tower2.png");
		isTowerSelected = true;
	}

	//top right
	if (mouse.x >= 118 && mouse.y >= 760 && mouse.x <= 118 + 50 && mouse.y <= 760 + 50) {
		hoverTower.loadFromFile("tower3.png");
		isTowerSelected = true;
	}

	//bottom left
	if (mouse.x >= 56 && mouse.y >= 816 && mouse.x <= 56 + 50 && mouse.y <= 816 + 50) {
		hoverTower.loadFromFile("tower1.png");
		isTowerSelected = true;
	}

	//bottom right
	if (mouse.x >= 118 && mouse.y >= 816 && mouse.x <= 118 + 50 && mouse.y <= 816 + 50) {
		hoverTower.loadFromFile("tower4.png");
		isTowerSelected = true;
	}





	//check sell button
	if (mouse.x >= 223 && mouse.y >= 758 && mouse.x <= 223 + 98 && mouse.y <= 758 + 28) {
		std::cout << "sell button\n";
	}

	//check buy button
	if (mouse.x >= 349 && mouse.y >= 758 && mouse.x <= 349 + 98 && mouse.y <= 758 + 28) {
		std::cout << "buy button\n";
	}

	//check upgrade button
	if (mouse.x >= 286 && mouse.y >= 814 && mouse.x <= 286 + 98 && mouse.y <= 814 + 28) {
		std::cout << "upgrade button\n";
	}

	//check menu button
	if (mouse.x >= 1002 && mouse.y >= 758 && mouse.x <= 1002 + 140 && mouse.y <= 758 + 30) {
		std::cout << "menu button\n";
	}
}


void Level::CheckMousePosition(sf::Vector2i mouse) {

	sf::Texture empty;
	
	for (int y = 0; y < BOARD_HEIGHT; y++)
		for (int x = 0; x < BOARD_WIDTH; x++) {

			if (isTowerSelected) {
				grid[x][y].LoadHoverTowerImage(hoverTower);

				if ((mouse.x > grid[x][y].getPosition().x && mouse.x < grid[x][y].getPosition().x + SPRITE_DIMENSION) && (mouse.y > grid[x][y].getPosition().y && mouse.y < grid[x][y].getPosition().y + SPRITE_DIMENSION)) {
					grid[x][y].setTowerTransperent(true);

					if (grid[x][y].getPurpose() == Purpose::BuildingPlace) {
						grid[x][y].setHoverTowerSpriteColor(sf::Color::Green);
					}
					else {
						grid[x][y].setHoverTowerSpriteColor(sf::Color::Red);
					}
				}
				else 
					grid[x][y].setTowerTransperent(false);
			}

			
		}
	
}

bool Level::isInsideASquare(int x, int y, int mx, int my) {
	
	if ((mx > grid[x][y].getPosition().x && mx < grid[x][y].getPosition().x + SPRITE_DIMENSION) && (my > grid[x][y].getPosition().y && my < grid[x][y].getPosition().y + SPRITE_DIMENSION))
		return true;
	else
		return false;

}

void Level::UpdateGame()
{

	if (waveSize > 0) {

		//Spawning
		if (this->spawnClock.getElapsedTime().asSeconds() >= 2) {
			ens = ens % waveSize;

			//if enemy is uninitialized
			if (!enemies[ens]->isVisible()) {
				//initialize
				enemies[ens]->setVisible(true);
				enemies[ens]->setPosition(sf::Vector2i(0, 4 * 48));
			}

			enemies[ens]->Move(grid);

			ens++;
			spawnClock.restart();
		}


		//Update enemy position (and maybe something else)
		if (this->enemyClock.getElapsedTime().asMilliseconds() >= 5) {

			en %= waveSize;

			enemies[en]->Move(grid);
			sf::Vector2i pos = enemies[en]->getPosition();
			pos.x = pos.x / SPRITE_DIMENSION;
			pos.y = pos.y / SPRITE_DIMENSION;

			if (grid[pos.x][pos.y].getPurpose() == Purpose::End) {
				delete enemies[en];
				waveSize--;
			}

			en++;
			enemyClock.restart();
		}
	}
	


}

void Level::PlaceTower(sf::Vector2i mouse)
{
	int x = mouse.x / SPRITE_DIMENSION;
	int y = mouse.y / SPRITE_DIMENSION;

	grid[x][y].LoadPlacedTowerImage(hoverTower, sf::Vector2i(x * SPRITE_DIMENSION, y * SPRITE_DIMENSION));
}

void Level::UnselectTower()
{
	this->isTowerSelected = false;

}
