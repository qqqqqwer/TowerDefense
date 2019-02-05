#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
class Menu
{
private:
	sf::Texture playButtonTexure;
	sf::Sprite playButtonSprite;

	sf::Texture exitButtonTexture;
	sf::Sprite exitButtonSprite;
	
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	void DrawMenu(sf::RenderWindow & window);
	void CheckMouseClicks(sf::Vector2i mouse, constants::GameState &state, Game & game, sf::RenderWindow & window);
	Menu();
};

