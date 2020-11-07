#include "HumanManager.h"

//Instantiate HumanManager singleton
HumanManager* HumanManager::getInstance() {
	if (!instance)
		instance = new HumanManager;
	return instance;
}

//Add a human
void HumanManager::push_back(Human h) {
	v.push_back(h);
}

//Update position of all Humans
void HumanManager::update(sf::Time dt) {
	for (auto i = v.begin(); i != v.end(); i++)
		i->update(dt);
}

//Draw all Humans
void HumanManager::draw(sf::RenderWindow& wnd) {
	for (auto i = v.begin(); i != v.end(); i++)
		i->draw(wnd);
}