#include "Level.h"

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
				grid[x][y].Init(x, y, emptyTexture);

			if (s == 1)
				grid[x][y].Init(x, y, pathTexture);

			if (s == 2)
				grid[x][y].Init(x, y, towerPlacementTexture);

		}
		std::cout << "\n";
	}



	levelFile.close();
}

void Level::Initialize(int levelNumber) {
	this->levelNumber = levelNumber;
	LoadMap();
	SetUpUI();
}

void Level::DrawLevel(sf::RenderWindow & window) {

	window.draw(background);
	window.draw(menu);

	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 25; x++) {
			grid[x][y].DrawSquare(window);
			//std::cout << grid[x][y].getPosition().x << " " << grid[x][y].getPosition().y << "\n";
		}
	}
}

void Level::CheckMouseClicks(sf::Vector2i mouse) {

	//check grid clicks
	for (int y = 0; y < BOARD_HEIGHT; y++)
		for (int x = 0; x < BOARD_WIDTH; x++) {
			if ((mouse.x > grid[x][y].getPosition().x && mouse.x < grid[x][y].getPosition().x + SPRITE_DIMENSION) && (mouse.y > grid[x][y].getPosition().y && mouse.y < grid[x][y].getPosition().y + SPRITE_DIMENSION)) {
				grid[x][y].SetColor(sf::Color::Green);
				std::cout << x << " " << y << "\n";
				return;
			}
		}


	//check tower buttons
	if (mouse.x >= 56 && mouse.y >= 760 && mouse.x <= 56 + 50 && mouse.y <= 760 + 50) {
		std::cout << "first tower\n";
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

void Level::AddRectangleShape(float  x, float y, float width, float height) {

	sf::RectangleShape button;
	button.setPosition(sf::Vector2f(x, y));
	button.setSize(sf::Vector2f(width, height));


}

void Level::SetUpUI() {



}