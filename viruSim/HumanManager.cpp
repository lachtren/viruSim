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
		check -= dt.asMicroseconds() * 1000;
		if (check <= 0)
		{
			//check_collision();
			check = 250;
			std::cout << "CHECK";
		}
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
	for (auto i = v.begin(); i != v.end(); i++)
	{
		for (auto j = v.begin(); j != v.end(); j++)
		{
			if (j != i)
			{
				auto x1 = (i->get_pos()).x;
				auto x2 = (j->get_pos()).x;
				auto y1 = (i->get_pos()).y;
				auto y2 = (j->get_pos()).y;
			}
		}
	}
}