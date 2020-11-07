#pragma once
#include "Human.h"
/*
Manages all Human objects. Currently handles drawing and updating.
Need to implement collision detection and handling
*/

class HumanManager
{
	static HumanManager* instance;
	HumanManager() {}
	std::vector<Human>v;
public:
	static HumanManager* getInstance();
	void push_back(Human);
	void update();
	void draw(sf::RenderWindow&);
};
