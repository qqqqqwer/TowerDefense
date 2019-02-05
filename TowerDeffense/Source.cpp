#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Constants.h"
#include "Game.h"
#include "Square.h"
#include "Menu.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Window", sf::Style::Titlebar | sf::Style::Close);

	Game game;
	Menu menu;
	constants::GameState state = constants::GameState::Menu;

	while (window.isOpen()) {

		sf::Event e;
		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed) {
				window.close();
			}


			if (state == constants::GameState::InGame) {
				if (e.type == sf::Event::MouseButtonPressed) {
					game.CheckMouseClicks(sf::Mouse::getPosition(window));
				}

				if (e.type == sf::Event::KeyPressed) {

					if (e.key.code == sf::Keyboard::Escape) {
						game.isGamePaused() ? game.ResumeGame() : game.UnselectTower(sf::Mouse::getPosition(window));
					}	
				}
			}
			else {
				if (e.type == sf::Event::MouseButtonPressed) {
					menu.CheckMouseClicks(sf::Mouse::getPosition(window), state, game, window);
				}
			}
			
			if (state == constants::GameState::InGame) {
				game.CheckMousePosition(sf::Mouse::getPosition(window));
			}

		}
		window.clear();

		if (state == constants::GameState::InGame) {
			game.UpdateGame();
			game.DrawLevel(window);
		}
		else {
			menu.DrawMenu(window);
		}

		window.display();
	}

	return 0;
}