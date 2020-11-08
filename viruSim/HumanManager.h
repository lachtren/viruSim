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
	void check_collision(sf::Time); //Cant figure this out
	int check = 250;
};