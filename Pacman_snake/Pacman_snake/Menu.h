#pragma once
void setText(sf::Font &font,sf::Text &screenText,const std::string &text, sf::Vector2f pos, int size);
class Menu {
	sf::Text pacman_snake;
	sf::Text ghost_number;
	sf::Text play;
	sf::Text quit;
	sf::Text number;
	sf::Sprite pointer;
	sf::Texture cherry;
	int menuScroll;
public:
	Menu(sf::Font &font);
	Menu();
	~Menu();

	virtual void draw(sf::RenderWindow &window);
	bool pressedKey(sf::Keyboard::Key key, int &number, sf::RenderWindow &window);
private:
	void scroll(sf::Keyboard::Key key);
	void changeGhostsAmount(sf::Keyboard::Key key, int &number);
	void changePointer();
};
