#include "HumanManager.h"
#include <iostream>

//Instantiate HumanManager singleton
HumanManager *HumanManager::getInstance()
{
	if (!instance)
		instance = new HumanManager;
	return instance;
}

//Add a human
void HumanManager::push_back(Human h)
{
	v.push_back(h);
}

//Update position of all Humans
void HumanManager::update(sf::Time dt)
{
	for (auto i = v.begin(); i != v.end(); i++)
	{
		i->check_wall();
		i->update_section();
		i->update(dt);
	}
}

//Draw all Humans
void HumanManager::draw(sf::RenderWindow &wnd)
{
	for (auto i = v.begin(); i != v.end(); i++)
		i->draw(wnd);
}

void HumanManager::check_collision()
{
}

int HumanManager::count_inf() {
	return std::count_if(v.begin(), v.end(), [](Human h) {
		return h.getInfected();
		});
}

int HumanManager::population() {
	return v.size();
}