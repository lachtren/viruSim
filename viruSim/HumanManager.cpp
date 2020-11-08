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
			for (auto itr_2 = itr + 1; itr_2 != v.end(); itr_2++)
			{
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
							if (itr->getInfected() || itr_2->getInfected()) {
								itr->setInfected(true);
								itr_2->setInfected(true);
								itr->setState(itr->width);
								itr->update_color(itr->width);
								itr_2->setState(itr->width);
								itr_2->update_color(itr->width);
							}
							/*
							itr->setMask(true); //THis just changes the mask color so we could see if collision worked
							
							itr_2->setMask(true);
							
							std::cout << "collison" << std::endl;
							*/
						}
					}
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