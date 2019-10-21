#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include "Ghost.h"


Ghost::Ghost() : Pacman("Ghost")
{
	sprite.setPosition(540, 580);
	this->flagTrolleyHit = false;
}


Ghost::~Ghost()
{
	
}

bool Ghost::check_trolleyHit(sf::Vector2f trolleyPosition)
{

	for (int i = 0; i < pacman->getCounter(); i++) {
		//std::cout << pacman->trolleys[i].getPosition().x<<" "<<pacman->trolleys[i].getPosition().y << "++++++++" << trolleyPosition.x << " " << trolleyPosition.y << std::endl;
		if (pacman->trolleys[i].getPosition() == trolleyPosition) {
			return true;
		}
		
	}
	
	return false;
}

void Ghost::auto_move(std::vector<std::vector<int>> map)
{
	int los;
		if (pressedKey == sf::Keyboard::T) {
			do {
				los = rand() % 4;
				if (los == 0) pressedKey = sf::Keyboard::W;
				if (los == 1) pressedKey = sf::Keyboard::A;
				if (los == 2) pressedKey = sf::Keyboard::S;
				if (los == 3) pressedKey = sf::Keyboard::D;
			} while (!move_pac(map));
		}
		else if (pressedKey == sf::Keyboard::W) {
			do {
				los = rand() % 3;
				if (los == 0) pressedKey = sf::Keyboard::W;
				if (los == 1) pressedKey = sf::Keyboard::A;
				if (los == 2) pressedKey = sf::Keyboard::D;
			} while (!move_pac(map) );
		}
		else if (pressedKey == sf::Keyboard::A) {
			do {
				los = rand() % 3;
				if (los == 0) pressedKey = sf::Keyboard::W;
				if (los == 1) pressedKey = sf::Keyboard::S;
				if (los == 2) pressedKey = sf::Keyboard::A;
			} while (!move_pac(map) );
		}
		else if (pressedKey == sf::Keyboard::S) {
			do {
				los = rand() % 3;
				if (los == 0) pressedKey = sf::Keyboard::A;
				if (los == 1) pressedKey = sf::Keyboard::S;
				if (los == 2) pressedKey = sf::Keyboard::D;
			} while (!move_pac(map));
		}
		else if (pressedKey == sf::Keyboard::D) {
			do {
				los = rand() % 3;
				if (los == 0) pressedKey = sf::Keyboard::W;
				if (los == 1) pressedKey = sf::Keyboard::S;
				if (los == 2) pressedKey = sf::Keyboard::D;
			} while (!move_pac(map));
		}
}

void Ghost::reset_texture()
{
	//load_textures();
	sprite.setTexture(texture);
}

void Ghost::set_ptr(TrolleyGhost *pacman)
{
	this->pacman = pacman;
}

void Ghost::reset()
{

}


bool Ghost::move_pac(std::vector<std::vector<int>> map)
{
	switch (pressedKey) {
	case sf::Keyboard::W:
		if (can_it_move(map)) {
			sprite.setTextureRect(sf::IntRect(72, 0, 36, 36));
			sprite.move(0, -40.0);
			return true;
		}
		break;
	case sf::Keyboard::A:
		if (portal()) {
			sprite.setTextureRect(sf::IntRect(36, 0, 36, 36));
			sprite.move(1080, 0);
			return true;
		}
		if (can_it_move(map)) {
			sprite.setTextureRect(sf::IntRect(36, 0, 36, 36));
			sprite.move(-40.0, 0);
			return true;
		}
		break;
	case sf::Keyboard::S:
		if (can_it_move(map)) {
			sprite.setTextureRect(sf::IntRect(108, 0, 36, 36));
			sprite.move(0, 40.0);
			return true;
		}
		break;
	case sf::Keyboard::D:
		if (portal()) {
			sprite.setTextureRect(sf::IntRect(0, 0, 36, 36));
			sprite.move(-1080, 0);
			return true;
		}
		if (can_it_move(map)) {
			sprite.setTextureRect(sf::IntRect(0, 0, 36, 36));
			sprite.move(40.0, 0);
			return true;
		}
		break;
	}
	if (flagTrolleyHit) {
		flagTrolleyHit = false;
		if (pressedKey == sf::Keyboard::W) pressedKey = sf::Keyboard::S;
		else if (pressedKey == sf::Keyboard::A) pressedKey = sf::Keyboard::D;
		else if (pressedKey == sf::Keyboard::S) pressedKey = sf::Keyboard::W;
		else if (pressedKey == sf::Keyboard::D) pressedKey = sf::Keyboard::A;
		move_pac(map);
		return true;
	}
	return false;
}

bool Ghost::can_it_move(std::vector<std::vector<int>> map){
	float x, y, x_next, y_next;
	int x_int, y_int;
	x = sprite.getPosition().x;
	y = sprite.getPosition().y;
	x -= 20;
	y -= 20;
	x /= 40;
	y /= 40;
	x_int = x;
	y_int = y;
	if (pressedKey==sf::Keyboard::W) y_int--;
	else if (pressedKey == sf::Keyboard::S) y_int++;
	else if (pressedKey == sf::Keyboard::A) x_int--;
	else if (pressedKey == sf::Keyboard::D) x_int++;
	x = x_int;
	y = y_int;
	x_next = (x * 40) + 20;
	y_next = (y * 40) + 20;
	
	//std::cout << x_next << "-------" << y_next <<"xxx"<< sprite.getPosition().x<<" "<<sprite.getPosition().y << std::endl;
	if (check_trolleyHit(sf::Vector2f(x_next, y_next))) {
		flagTrolleyHit = true;
		return false;
	}
	if (sprite.getPosition().x == 500 && sprite.getPosition().y == 580 && pressedKey == sf::Keyboard::A) {
		flagTrolleyHit = true;
		return false;
	}
	if (sprite.getPosition().x == 620 && sprite.getPosition().y == 580 && pressedKey == sf::Keyboard::D) {
		flagTrolleyHit = true;
		return false;
	}
	if (map[x_int][y_int]) {
		//std::cout << "no " << x_int << " " << y_int << std::endl;
		return false;
	}
	//std::cout << "yes " << x_int << " " << y_int << std::endl;
	return true;
}


