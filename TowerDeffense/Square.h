#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"

class Square {
private:
	sf::Sprite sprite;
	sf::Sprite hoverSprite;
	sf::Sprite placedTower;
	constants::Purpose p;
	sf::Vector2i position;

	sf::CircleShape towersRange; 

	std::string type;
	int damage;
	int range;
	int fireRate;
	sf::CircleShape rangeIndicator;
	int upgradePrice;
	int sellPrice;

public:
	sf::Clock fireRateClock;
	void setHoverTower(sf::Sprite & sprite);
	void LoadImage(sf::Texture & texture);
	void Init(int x, int y, sf::Texture & texture, constants::Purpose pur);
	void DrawSquare(sf::RenderWindow & window);
	sf::Vector2i getPosition();
	void SetColor(sf::Color color);
	sf::Sprite getSprite();
	void LoadHoverTowerImage(sf::Texture & texture);
	void setTowerTransperent(bool trans);
	void setHoverTowerSpriteColor(sf::Color color);
	constants::Purpose getPurpose();
	void PlaceTower(sf::Texture & texture, sf::Vector2i pos, int type);
	void setHoverTowerVisible(bool vis);
	std::tuple<int, int, int> getTowerStats();
	int Sell();
	void Upgrade();
	int getUpgradePrice();
};