#pragma once
#include "Pacman.h"

class TrolleyGhost : public Pacman {
	int counter;
	sf::Texture trolleyTexture;
public:
	sf::Sprite trolleys[50];
	bool isAlive;

	TrolleyGhost();
	~TrolleyGhost();
	
	virtual void draw(sf::RenderWindow &window);
	void collision_detected();
	int getCounter();
	void reset();
	bool set_key(sf::Keyboard::Key key, int framerate, std::vector<std::vector<int>> map);

private:
	virtual bool move_pac(std::vector<std::vector<int>> map);
	void update_trolleys();
	void check_hit();
};