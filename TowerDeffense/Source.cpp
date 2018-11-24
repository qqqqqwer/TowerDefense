#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define BOARD_WIDTH 25
#define BOARD_HEIGHT 15
#define SPRITE_DIMENSION 48
#define PLAYFIELD_WIDTH 1200
#define PLAYFIELD_HEIGHT 720

enum class Purpose
{
	Ambient,
	Tower,
	Path,
	BuildingPlace
};

class Square {
private:
	//Sprite uses a texture
	sf::Sprite sprite;
	sf::Vector2f position;
	Purpose p;

public:
	void LoadImage(sf::Texture & texture) {
		sprite.setTexture(texture);
	}

	void Init(float x, float y, sf::Texture & texture) {
		position = sf::Vector2f(x * SPRITE_DIMENSION, y * SPRITE_DIMENSION);
		LoadImage(texture);
		sprite.setPosition(position);
	}

	void DrawSquare(sf::RenderWindow & window) {
		window.draw(sprite);
	}
};

class Tower : public Square {

private:
	int range;
	int damage;
	int fireRate;
	int sellPrice;

	sf::Sprite towerSprite;
	sf::Sprite bulletSprite;
};

class Level {

private:
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
	

	Square grid[BOARD_WIDTH][BOARD_HEIGHT];
	std::vector<sf::RectangleShape> buttons; 

	void LoadMap() {
		

		emptyTexture.create(SPRITE_DIMENSION, SPRITE_DIMENSION);
		pathTexture.loadFromFile("path.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));
		tower1Texture.loadFromFile("tower1.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));
		towerPlacementTexture.loadFromFile("TowerPlacement.png", sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));


		std::ifstream levelFile("level" + std::to_string(levelNumber) + ".txt");
		std::cout << "level" + std::to_string(levelNumber) + ".txt" << "\n";


		backgroundTexture.loadFromFile("level" + std::to_string(levelNumber) + ".png", sf::IntRect(0, 0, PLAYFIELD_WIDTH, PLAYFIELD_HEIGHT));
		background.setTexture(backgroundTexture);

		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 25; x++) {
				int s;
				levelFile >> s;

				std::cout << s << " ";

				if (s == 0)
					grid[x][y].Init((float)x, (float)y, emptyTexture);

				if (s == 1)
					grid[x][y].Init((float)x, (float)y, pathTexture);

				if (s == 2)
					grid[x][y].Init((float)x, (float)y, towerPlacementTexture);

			}
			std::cout << "\n";
		}



		levelFile.close();
	}

public:
	void Initialize(int levelNumber) {
		this->levelNumber = levelNumber;
		LoadMap();
		SetUpUI();
	}

	

	void DrawLevel(sf::RenderWindow & window) {


		window.draw(background);

		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 25; x++) {
				grid[x][y].DrawSquare(window);
			}
		}
	}

	void AddRectangleShape(float  x, float y, float width, float height) {

		sf::RectangleShape button;
		button.setPosition(sf::Vector2f(x, y));
		button.setSize(sf::Vector2f(width, height));
		

	}

	void SetUpUI() {



	}
};

//Class that loads levels lol
class LevelManager {

public: 
	static void LoadLevel(Level (& levels)[1], int level) {
		levels[level].Initialize(level);
	}

};


class UI {

private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture extraMenuTexture;
	sf::Sprite extraMenu;

	sf::Texture tower1ButtonTexture;
	sf::Sprite tower1Button;

	sf::Texture tower2ButtonTexture;
	sf::Sprite tower2Button;

	sf::Texture tower3ButtonTexture;
	sf::Sprite tower3Button;

	sf::Texture tower4ButtonTexture;
	sf::Sprite tower4Button;


public:
	void Initialize() {
		 
		backgroundTexture.loadFromFile("UIBackground.png");
		extraMenuTexture.loadFromFile("Extramenu.png");
		tower1ButtonTexture.loadFromFile("tower1Button.png");

	}
};

class Monster {
	 
	int health;
	int speed;
	sf::Texture monsterTexture;
	sf::Sprite monsterSprite;

};

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Window", sf::Style::Titlebar | sf::Style::Close);

	Level levels[1];
	LevelManager::LoadLevel(levels, 0);

	levels[0].DrawLevel(window);

	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(1200, 180));
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(sf::Vector2f(0, 720));
	window.draw(shape);
	window.display();

	while (window.isOpen()) {

		sf::Event e;
		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed) {
				window.close();
			}

		}
	}

	return 0;
}