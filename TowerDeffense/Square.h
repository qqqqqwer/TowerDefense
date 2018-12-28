#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"


class Square {
private:
	//Sprite uses a texture
	sf::Sprite sprite;
	sf::Sprite hoverSprite;
	sf::Sprite placedTower;
	Purpose p;
	sf::Vector2i position;
	bool towerIsPlaced;
public:
	void setHoverTower(sf::Sprite & sprite);
	void LoadImage(sf::Texture & texture);
	void Init(int x, int y, sf::Texture & texture, Purpose pur);
	void DrawSquare(sf::RenderWindow & window);
	sf::Vector2i getPosition();
	void SetColor(sf::Color color);
	sf::Sprite getSprite();
	void setSprite(sf::Sprite & sprt);
	void LoadHoverTowerImage(sf::Texture & texture);
	void setTowerTransperent(bool trans);
	void setHoverTowerSpriteColor(sf::Color color);
	Purpose getPurpose();
	void LoadPlacedTowerImage(sf::Texture & texture, sf::Vector2i pos);
	void setHoverTowerVisible(bool vis);
	bool isTowerPlaced();
};