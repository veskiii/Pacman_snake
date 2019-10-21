#pragma once
#include "Pacman.h"
#include "TrolleyGhost.h"

class Ghost : public Pacman {
	TrolleyGhost *pacman;
	bool flagTrolleyHit;
public:
	Ghost();
	
	~Ghost();

	void auto_move(std::vector<std::vector<int>> map);
	void reset_texture();
	void set_ptr(TrolleyGhost *pacman);
	void reset();
private:
	virtual bool move_pac(std::vector<std::vector<int>> map);
	virtual bool can_it_move(std::vector<std::vector<int>> map);
	bool check_trolleyHit(sf::Vector2f trolleyPosition);
};

