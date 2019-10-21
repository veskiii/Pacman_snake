#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include "TrolleyGhost.h"

TrolleyGhost::TrolleyGhost()
{
	this->counter = 0;
	if (!this->trolleyTexture.loadFromFile("res\\TrolleyGhost.png")) std::cout << "trolleyTexture loading failed.";
	for (int i = 0; i < 50; i++) {
		trolleys[i].setOrigin(20, 20);
		trolleys[i].setPosition(sf::Vector2f(580, 580));
		trolleys[i].setTexture(trolleyTexture);
	}
	this->isAlive = true;
}

TrolleyGhost::~TrolleyGhost()
{
}

bool TrolleyGhost::move_pac(std::vector<std::vector<int>> map)
{
	if (portal() || can_it_move(map)) {
		update_trolleys();
		if (pressedKey == sf::Keyboard::W) {
			sprite.setTextureRect(sf::IntRect(72, 0, 36, 36));
			sprite.move(0, -40.0);
			return true;
		}
		if (pressedKey == sf::Keyboard::A) {
			sprite.setTextureRect(sf::IntRect(36, 0, 36, 36));
			if (portal()) sprite.move(1080, 0);
			else sprite.move(-40.0, 0);
			return true;
		}
		if (pressedKey == sf::Keyboard::S) {
			sprite.setTextureRect(sf::IntRect(108, 0, 36, 36));
			sprite.move(0, 40.0);
			return true;
		}
		if (pressedKey == sf::Keyboard::D) {
			sprite.setTextureRect(sf::IntRect(0, 0, 36, 36));
			if (portal()) sprite.move(-1080, 0);
			else sprite.move(40.0, 0);
			return true;
		}
	}
	return false;
}

void TrolleyGhost::update_trolleys()
{
	for (int i = 49; i > 0; i--) {
		trolleys[i].setPosition(trolleys[i - 1].getPosition());
		trolleys[i].setTextureRect(trolleys[i - 1].getTextureRect());
	}
	trolleys[0].setPosition(sprite.getPosition());
	trolleys[0].setTextureRect(sprite.getTextureRect());
}

void TrolleyGhost::check_hit()
{
	for (int i = 0; i < counter; i++) {
		if (sprite.getPosition() == trolleys[i].getPosition()) {
			isAlive = false;
			return;
		}
	}
	isAlive = true;
}

void TrolleyGhost::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
	for (int i = 0; i < counter; i++) {
		window.draw(trolleys[i]);
	}
}

void TrolleyGhost::collision_detected()
{
	this->counter++;
}

int TrolleyGhost::getCounter()
{
	return counter;
}

void TrolleyGhost::reset()
{
	sprite.setPosition(60, 60);
	counter = 0;
	isAlive = true;
	pressedKey = sf::Keyboard::T;
}

bool TrolleyGhost::set_key(sf::Keyboard::Key key, int framerate, std::vector<std::vector<int>> map)
{
	this->pressedKey = key;
	if (framerate == 0 && isAlive == true) {
		if (move_pac(map)) {
			check_hit();
			return true;
		}
	}
	return false;
}
