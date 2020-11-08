#include "HumanManager.h"
#include <iostream>
#include <cmath>

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

void HumanManager::check_collision(sf::Time dt)
{
	check_timer -= dt.asMicroseconds() / 1000;
	if(check_timer <=0){
		for (auto itr = v.begin(); itr != v.end() - 1; itr++)
		{
			if(!itr->colliding){
			for (auto itr_2 = itr + 1; itr_2 != v.end(); itr_2++)
			{
				if(itr->colliding_cd <=0  && itr_2->colliding_cd <= 0){
					if (itr->section.first + 1 == itr_2->section.first ||
						itr->section.first - 1 == itr_2->section.first
						|| itr->section.first == itr_2->section.first)
					{
						if (itr->section.second + 1 == itr_2->section.second ||
							itr->section.second - 1 == itr_2->section.second
							|| itr->section.second == itr_2->section.second)
						{
							//std::cout << "close to collision" << std::endl;
							if (std::sqrt(std::pow(itr->get_pos().x - itr_2->get_pos().x, 2) +
								std::pow(itr->get_pos().y - itr_2->get_pos().y, 2)) < (2 * itr->r)) {
								itr->colliding = 1;
								itr_2->colliding = 1;
								if (itr->getInfected() || itr_2->getInfected()) {
									itr->setInfected(true);
									itr_2->setInfected(true);
								}
							}
						}
					}
				}
				if (itr->colliding_cd >= 0)
					itr->colliding_cd -= dt.asMicroseconds()/1000;
				if (itr_2->colliding_cd >= 0)
					itr_2->colliding_cd -= dt.asMicroseconds() / 1000;
				}
			}
		}
		check_timer = 250;
	}
}

int HumanManager::count_inf() {
	return std::count_if(v.begin(), v.end(), [](Human h) {
		return h.getInfected();
		});
}

int HumanManager::population() {
	return v.size();
}

void HumanManager::update_collisions(sf::Time dt) {
	int time = dt.asMicroseconds() / 1000;
	for (auto itr = v.begin(); itr != v.end(); itr++) {
		if(itr->colliding)
		itr->update_colission(time);
	}
}