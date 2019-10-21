#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Ghost.h"
#include "TileMap.h"
#include "Pacman.h"
#include "TrolleyGhost.h"
#include "Other.h"
#include "Menu.h"


int main()
{
	srand((unsigned)time(NULL));
	sf::RenderWindow window{ {1120,1240}, "Window name" };
	window.setActive(true);
	window.setVerticalSyncEnabled(true);
	int frameRate = 0;
	int fps = 0;

	// WIN / LOSE   BOARDS ---------------------------------------------------------
	sf::RectangleShape board;
	board.setSize(sf::Vector2f(560, 400));
	board.setOrigin(sf::Vector2f(280, 200));
	board.setPosition(sf::Vector2f(560, 580));
	sf::Texture Board;
	if (!Board.loadFromFile("res\\Boards.png")) std::cout << "Wszystko NIE gituwa";
	board.setTexture(&Board);
	board.setTextureRect(sf::IntRect(0, 0, 560, 400));

	// CHARACTERS -----------------------------------------------------------------
	TrolleyGhost pacman;
	TrolleyGhost *pac_ptr = &pacman;

	int numberOfGhosts = 1;
	std::vector<Ghost> ghosts;
	ghosts.resize(numberOfGhosts);
	for (int i = 0; i < numberOfGhosts; i++) {
		ghosts[i].set_ptr(pac_ptr);
	}


	// MAP ------------------------------------------------------------------------
	std::vector<std::vector<int>> map = load_map();
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}
	TileMap tileMap;
	if (!tileMap.load("res\\tileset.png", sf::Vector2u(40, 40), map, 28, 31)) std::cout << "Tilemap load failed..." << std::endl;
	
	// MENU =========================================================================
	window.setKeyRepeatEnabled(false);
	window.clear(sf::Color(4,4,84));
	sf::Font font;
	if (!font.loadFromFile("res\\boldFont.ttf"))
		std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
	Menu menu(font);

	//===============================================================================
	// FLAGS ------------------------------------------------------------------------
	sf::Keyboard::Key lastPressed = sf::Keyboard::T;
	bool flagEnd = 0;
	bool flagBegin = 0;
	bool flagGhostsInside = 1;
	bool flagGhostsMovingOut = 0;
	bool flagMenu = 1; //ustaw potem na 1

	//===============================================================================
	// MAIN LOOP --------------------------------------------------------------------
	//===============================================================================
	while (window.isOpen()) {
		sf::Event windowEvent;
		fps++;
		// EVENT LOOP ---------------------------------------------------------------
		while (window.pollEvent(windowEvent)) {
			if (flagEnd) {//duszki reset
				pacman.reset();
				//for (int i = 0; i < ghosts.size(); i++)
					//ghosts.pop_back();
				ghosts.clear();
				flagEnd = 0;
				flagBegin = 0;
				flagGhostsInside = 1;
				flagGhostsMovingOut = 0;
				flagMenu = 1;
			}
			else {
				if (windowEvent.type == sf::Event::Closed)
					window.close();
				if (windowEvent.type == sf::Event::KeyPressed) {
					if (windowEvent.key.code == sf::Keyboard::Escape)
						window.close();
					if (!flagMenu)
						lastPressed = windowEvent.key.code;
					else
						if (menu.pressedKey(windowEvent.key.code, numberOfGhosts, window)) {
							flagMenu = false;
							window.setKeyRepeatEnabled(true);
						}
				}
			}
		}

		if (!flagMenu) {
			if (!flagEnd) {
				if (pacman.set_key(lastPressed, frameRate, map)) {
					flagBegin = true;
				}
				if (flagBegin && flagGhostsInside) {
					openGate(map, tileMap);
					flagGhostsMovingOut = true;
					flagGhostsInside = false;
				}
				if (flagGhostsMovingOut) {
					if (checkGhosts(ghosts)) {
						closeGate(map, tileMap);
						flagGhostsMovingOut = false;
					}
				}
				detect_collision(ghosts, pacman);
				for (int i = 0; i < ghosts.size(); i++)
					ghosts[i].auto_move(map);

				detect_collision(ghosts, pacman);
			}

			// DRAWING --------------------------------------------------------------------
			window.clear();
			window.draw(tileMap);
			pacman.draw(window);
			for (int i = 0; i < ghosts.size(); i++)
				ghosts[i].draw(window);
			if (endGame(pacman, ghosts, tileMap, map, board)) {
				window.draw(board);
				flagEnd = 1;
			}
		}// Menu =========================================================================
		else {
			//menu.pressedKey(lastPressed, numberOfGhosts);
			ghosts.resize(numberOfGhosts);
			for (int i = 0; i < numberOfGhosts; i++) {
				ghosts[i].set_ptr(pac_ptr);
				ghosts[i].reset_texture();
			}

			window.clear(sf::Color(4, 4, 84));
			menu.draw(window);
		}
		window.display();

		// FPS COUNTER ----------------------------------------------------------------
		frameRate++;
		if (frameRate == 4) frameRate = 0;
		if (!(fps % 60)) {
			std::cout << '.';
			fps = 0;
		}
	}
	return 0;
}

