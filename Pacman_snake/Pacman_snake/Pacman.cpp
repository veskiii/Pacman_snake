#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include "Pacman.h"

Pacman::Pacman(std::string name)
{
	this->name = name;
	if (!load_texture()) std::cout << "Loading texture failed." << std::endl;
	sprite.setOrigin(20, 20);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 36, 36));
	this->pressedKey = sf::Keyboard::T;
}

Pacman::Pacman()
{
	this->name = "Pacman";
	if (!load_texture()) std::cout << "Loading texture failed." << std::endl;
	sprite.setOrigin(20, 20);
	sprite.setPosition(60, 60);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0,36,36));
	this->pressedKey = sf::Keyboard::T;
}

Pacman::~Pacman()
{
}


void Pacman::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}


bool Pacman::can_it_move(std::vector<std::vector<int>> map)
{
	float x, y;
	int x_int, y_int;
	x = sprite.getPosition().x;
	y = sprite.getPosition().y;
	x /= (float)1120;
	y /= (float)1240;
	x *= 28;
	y *= 31;
	x_int = x;
	y_int = y;
	if (pressedKey == sf::Keyboard::W) y_int--;
	else if (pressedKey == sf::Keyboard::S) y_int++;
	else if (pressedKey == sf::Keyboard::A) x_int--;
	else if (pressedKey == sf::Keyboard::D) x_int++;
	if (map[x_int][y_int]) {
		//std::cout << "no " << x_int << " " << y_int << std::endl;
		return false;
	}
	//std::cout << "yes " << x_int << " " << y_int << std::endl;
	return true;
}

bool Pacman::portal()
{
	float x, y;
	int x_int, y_int;
	x = sprite.getPosition().x;
	y = sprite.getPosition().y;
	x /= (float)1120;
	y /= (float)1240;
	x *= 28;
	y *= 31;
	x_int = x;
	y_int = y;
	if ((x_int == 0 && y_int == 14 && pressedKey == sf::Keyboard::A) || (x_int == 27 && y_int == 14 && pressedKey == sf::Keyboard::D)) return true;
	return false;
}

std::string Pacman::getName()
{
	return this->name;
}

bool Pacman::load_texture()
{
	std::string tmp;
	tmp = "res\\" + name + ".png";
	if(!texture.loadFromFile(tmp)) return false;
	return true;
}
