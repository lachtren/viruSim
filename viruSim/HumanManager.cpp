#include "HumanManager.h"

//Instantiate HumanManager singleton
HumanManager* HumanManager::getInstance() {
	if (!instance)
		instance = new HumanManager;
	return instance;
}

void HumanManager::push_back(Human h) {
	v.push_back(h);
}

//Update position of all Humans
void HumanManager::update() {
	for (auto i = v.begin(); i != v.end(); i++)
		i->update();
}

//Draw all Humans
void HumanManager::draw(sf::RenderWindow& wnd) {
	for (auto i = v.begin(); i != v.end(); i++)
		i->draw(wnd);
}