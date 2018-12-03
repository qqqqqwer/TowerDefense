#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"

class Square {
private:
	//Sprite uses a texture
	sf::Sprite sprite;
	Purpose p;
	sf::Vector2i position;
public:
	void LoadImage(sf::Texture & texture);
	void Init(int x, int y, sf::Texture & texture);
	void DrawSquare(sf::RenderWindow & window);
	sf::Vector2i getPosition();
};