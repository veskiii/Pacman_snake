#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"

Menu::Menu(sf::Font &font)
{
	setText(font,pacman_snake, "pacman_snake", sf::Vector2f(35, 30), 136);
	setText(font,ghost_number, "Ghosts number:", sf::Vector2f(130, 450), 70);
	setText(font,play, "PLAY", sf::Vector2f(450, 550), 70);
	setText(font,quit, "Quit", sf::Vector2f(450, 1050), 70);
	setText(font,number, "< "+ std::to_string(1)+" >", sf::Vector2f(800, 450), 70);

	
	if (!cherry.loadFromFile("res\\cherry.png"))
		std::cout << "Texture cherry loading failed." << std::endl;
	pointer.setTexture(cherry);
	pointer.setOrigin(sf::Vector2f(20, 20));
	pointer.setPosition(sf::Vector2f(70, 490));

	menuScroll = 0;
}

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow & window)
{
	window.draw(pacman_snake);
	window.draw(ghost_number);
	window.draw(play);
	window.draw(quit);
	window.draw(number);
	window.draw(pointer);
}

bool Menu::pressedKey(sf::Keyboard::Key key, int &number, sf::RenderWindow &window)
{
	if (key == sf::Keyboard::W || key == sf::Keyboard::S)
		scroll(key);
	else if (key == sf::Keyboard::A || key == sf::Keyboard::D)
		changeGhostsAmount(key, number);
	else if (key == sf::Keyboard::Enter) {
		if (menuScroll == 1) {
			return true;
		}
		else if (menuScroll == 2) {
			window.close();
		}
	}
	return false;
}

void Menu::scroll(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::W) {
		menuScroll--;
	}
	else {
		menuScroll++;
	}
	if (menuScroll == -1) {
		menuScroll = 2;
	}
	else if (menuScroll == 3) {
		menuScroll = 0;
	}
	changePointer();
}

void Menu::changeGhostsAmount(sf::Keyboard::Key key, int & number)
{
	if (key == sf::Keyboard::A) {
		number--;
	}
	else {
		number++;
	}
	if (number == 0) {
		number = 50;
	}
	else if (number == 51) {
		number = 1;
	}
	this->number.setString("< " + std::to_string(number) + " >");
}

void Menu::changePointer()
{
	if (menuScroll == 0) pointer.setPosition(sf::Vector2f(70, 490));
	else if (menuScroll == 1) pointer.setPosition(sf::Vector2f(70, 590));
	else if (menuScroll == 2) pointer.setPosition(sf::Vector2f(70, 1090));
}

void setText(sf::Font &font, sf::Text &screenText,const std::string &text, sf::Vector2f pos, int size)
{
	sf::Color color(122, 4, 202);
	screenText.setFont(font);
	screenText.setString(text);
	screenText.setCharacterSize(size);
	screenText.setFillColor(color);
	screenText.setPosition(pos);
}
