#include "Menu.h"

void Menu::DrawMenu(sf::RenderWindow & window)
{
	window.draw(this->backgroundSprite);
	window.draw(playButtonSprite);
	window.draw(exitButtonSprite);
}

void Menu::CheckMouseClicks(sf::Vector2i mouse, constants::GameState &state, Game & game, sf::RenderWindow & window)
{

	float playX = PLAYFIELD_WIDTH / 2 - (float)(playButtonTexure.getSize().x / 2);
	float playY = PLAYFIELD_HEIGHT / 2;

	float exitX = PLAYFIELD_WIDTH / 2 - (float)(playButtonTexure.getSize().x / 2);
	float exitY = PLAYFIELD_HEIGHT / 2 + 100;

	if (mouse.x >= playX && mouse.y >= playY && mouse.x <= playX + playButtonTexure.getSize().x && mouse.y <= playY + playButtonTexure.getSize().y) {
		state = constants::GameState::InGame;
		game.Initialize();
	}
	else if (mouse.x >= exitX && mouse.y >= exitY && mouse.x <= exitX + playButtonTexure.getSize().x && mouse.y <= exitY + playButtonTexure.getSize().y) {
		window.close();
	}
	else {
		std::cout << "dis is not a button\n";
	}
}

Menu::Menu()
{
	this->backgroundTexture.loadFromFile("Menu.png");
	this->backgroundSprite.setTexture(this->backgroundTexture);

	this->playButtonTexure.loadFromFile("play button.png");
	this->playButtonSprite.setTexture(playButtonTexure);
	this->playButtonSprite.setPosition(PLAYFIELD_WIDTH / 2 - (float)(playButtonTexure.getSize().x / 2), PLAYFIELD_HEIGHT / 2);
	
	this->exitButtonTexture.loadFromFile("exit button.png");
	this->exitButtonSprite.setTexture(exitButtonTexture);
	this->exitButtonSprite.setPosition(PLAYFIELD_WIDTH / 2 - (float)(exitButtonTexture.getSize().x / 2), PLAYFIELD_HEIGHT / 2 + 100);
}