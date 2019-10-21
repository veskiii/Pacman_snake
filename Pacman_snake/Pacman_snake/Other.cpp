#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include "Other.h"

void detect_collision(std::vector<Ghost> &ghosts, TrolleyGhost &pacman) {
	for (int i = 0; i < ghosts.size(); i++) {
		if (ghosts[i].sprite.getPosition() == pacman.sprite.getPosition()) {
			pacman.collision_detected();
			std::swap(ghosts[i], ghosts.back());
			ghosts.pop_back();
			for (int j = 0; j < ghosts.size(); j++)
				ghosts[j].reset_texture();
			i--;
		}
	}
}

bool isLose(TrolleyGhost pacman)
{
	if (!pacman.isAlive) return true;
	return false;
}

bool isWin(TrolleyGhost pacman, std::vector<Ghost> ghosts, std::vector<std::vector<int>> &map, TileMap &tilemap)
{
	if (ghosts.size() == 0){
		openGate(map, tilemap);
		if (pacman.sprite.getPosition() == sf::Vector2f(540, 580) || pacman.sprite.getPosition() == sf::Vector2f(580, 580)) return true;
	}
	return false;
}

bool endGame(TrolleyGhost pacman, std::vector<Ghost> ghosts, TileMap &tilemap, std::vector<std::vector<int>> &map, sf::RectangleShape &board)
{
	if (isWin(pacman, ghosts, map, tilemap)) {
		board.setTextureRect(sf::IntRect(0, 400, 560, 400));
		return true;
	}
	else if (isLose(pacman)) {
		board.setTextureRect(sf::IntRect(0, 0, 560, 400));
		return true;
	}
	return false;
}

void openGate(std::vector<std::vector<int>>& map, TileMap &tilemap)
{
	map[13][15] = 0;
	map[13][16] = 0;
	map[14][15] = 0;
	map[14][16] = 0;
	map[12][15] = 9;
	map[12][16] = 7;
	map[15][15] = 8;
	map[15][16] = 6;
	tilemap.load("res\\tileset.png", sf::Vector2u(40, 40), map, 28, 31);
}

void closeGate(std::vector<std::vector<int>>& map, TileMap & tilemap)
{
	map[13][15] = 3;
	map[13][16] = 2;
	map[14][15] = 3;
	map[14][16] = 2;
	map[12][15] = 3;
	map[12][16] = 2;
	map[15][15] = 3;
	map[15][16] = 2;
	tilemap.load("res\\tileset.png", sf::Vector2u(40, 40), map, 28, 31);
}

bool checkGhosts(std::vector<Ghost> ghosts)
{
	for (int i = 0; i < ghosts.size(); i++) {
		if (ghosts[i].sprite.getPosition().x > 480 && ghosts[i].sprite.getPosition().x < 640
			&& ghosts[i].sprite.getPosition().y > 560 && ghosts[i].sprite.getPosition().y < 680) {

			return false;
		}
	}
	return true;
}

