#pragma once
#include "Ghost.h"
#include "TrolleyGhost.h"
#include "TileMap.h"

void detect_collision(std::vector<Ghost> &ghosts, TrolleyGhost &pacman);
bool isLose(TrolleyGhost pacman);
bool isWin(TrolleyGhost pacman, std::vector<Ghost> ghosts, std::vector<std::vector<int>> &map, TileMap &tilemap);
bool endGame(TrolleyGhost pacman, std::vector<Ghost> ghosts, TileMap &tilemap, std::vector<std::vector<int>> &map, sf::RectangleShape &board);
void openGate(std::vector<std::vector<int>> &map, TileMap &tilemap);
void closeGate(std::vector<std::vector<int>> &map, TileMap &tilemap);
bool checkGhosts(std::vector<Ghost> ghosts);
