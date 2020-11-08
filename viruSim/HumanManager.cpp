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

void HumanManager::handle_collisions(Human& h1, Human& h2)
{
	
	int status; // Will hold the values of infected or not
	//0 = neither infected
	//1 = one of the infected
	//2 = both infected

	if (h1.getInfected() && h2.getInfected())
		status = 2;
	else if (!(h1.getInfected() && h2.getInfected()))
		status = 1;
	else
		status = 0;

	if (status == 1) // Only run if one is infected 
	{
		int rand_num = rand() % 100; // create a random number to test for transimiton 
		//if one has mask and other doesnt
		if (h1.getMask() == true && h2.getMask() == false
			|| h1.getMask() == false && h2.getMask() == true) {
			
		}
		//if both have mask
		else if (h1.getMask() == true && h2.getMask() == true)
		{
			
		}
		//If neither have mask 
		else if (h1.getMask() == true && h2.getMask() == true)
		{
			
		}
	}
	else if (status == 0) // Do birth rate
	{
		int rand_num = rand() % 100; // create a random number to test for transimiton 
	}
	//if both infected dont do anything
	

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
								auto itr_for_ref = *itr;
								auto itr_2_for_ref = *itr;
								handle_collisions(itr_for_ref, itr_2_for_ref); //Reference of the human object

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

