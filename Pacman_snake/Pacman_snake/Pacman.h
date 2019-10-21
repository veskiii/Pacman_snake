#pragma once

class Pacman {
	std::string name;
protected:
	sf::Keyboard::Key pressedKey;
	sf::Texture texture;

public:
	sf::Sprite sprite;

	Pacman(std::string name);
	Pacman();
	~Pacman();

	virtual void draw(sf::RenderWindow &window);

protected:
	virtual bool can_it_move(std::vector<std::vector<int>> map);
	bool portal();
	std::string getName();

private:
	virtual bool move_pac(std::vector<std::vector<int>> map) = 0;
	bool load_texture();
	
};