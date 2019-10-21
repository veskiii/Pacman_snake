#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include "TileMap.h"

bool TileMap::load(const std::string & tileset, sf::Vector2u tileSize,  std::vector<std::vector<int>> tiles, unsigned int width, unsigned int height)
{
	if (!m_tileset.loadFromFile(tileset)) {
		std::cout << "Tileset loading failed." << std::endl;
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			int tileNumber = tiles[i][j];

			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &m_tileset;

	target.draw(m_vertices, states);
}

std::vector<std::vector<int>> load_map()
{
	std::vector<std::vector<int>> map;
	int tmp;
	map.resize(28);
	for (int i = 0; i < 28; i++) {
		map[i].resize(31);
	}
	std::ifstream file("res\\map.txt");
	while (!file.eof()) {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 28; j++) {
				file >> tmp;
				map[j][i] = tmp;
			}
		}
	}
	/*for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 28; j++)
			std::cout << map[i][j] << " ";
		std::cout << std::endl;
	}*/
	std::cout << "Map loaded." << std::endl;
	file.close();
	return map;
}
