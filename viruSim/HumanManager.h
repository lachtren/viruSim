#pragma once
#include "Human.h"
/*
Manages all Human objects. Currently handles drawing and updating.
Need to implement collision detection and handling
*/

class HumanManager
{
	int check_timer = 250;
	static HumanManager* instance;
	HumanManager() {}
	std::vector<Human>v;
public:
	static HumanManager* getInstance();
	void push_back(Human);
	void update(sf::Time);
	void draw(sf::RenderWindow&);
	int count_inf();
	int population();
	void update_collisions(sf::Time);
	void check_collision(sf::Time);
	int check = 250;
	void clear();
	void handle_collisions(Human& , Human&);
};