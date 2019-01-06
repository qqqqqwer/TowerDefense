#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Constants.h"
#include "Level.h"
#include "Square.h"
#include "Tower.h"


//Class that loads levels lol
class LevelManager {

public: 
	static void LoadLevel(Level (& levels)[1], int level) {
		levels[level].Initialize(level);
	}

	static void LoadMenu() {
		
	}

};


int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Window", sf::Style::Titlebar | sf::Style::Close);

	Level levels[1];
	LevelManager::LoadLevel(levels, 0);

	while (window.isOpen()) {

		sf::Event e;
		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed) {
				window.close();
			}

			if (e.type == sf::Event::MouseButtonPressed) {
				levels[0].CheckMouseClicks(sf::Mouse::getPosition(window));
			}

			if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::Escape) {
					levels[0].UnselectTower(sf::Mouse::getPosition(window));
				}
			}

			levels[0].CheckMousePosition(sf::Mouse::getPosition(window));
			
		}
		window.clear();

		levels[0].UpdateGame();
		levels[0].DrawLevel(window);

		window.display();
	}

	return 0;
}