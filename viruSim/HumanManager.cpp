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

int mask_eff;
int f_rate;
int b_rate;
int t_rate;


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

//Update the variables for the the collison deteection
void HumanManager::store_all_vars(int sim_t_rate,
	int sim_mask_eff,
	int sim_f_rate,
	int sim_b_rate) {

	t_rate = sim_t_rate;
	mask_eff = sim_mask_eff;
	f_rate = sim_f_rate;
	b_rate = sim_b_rate;
}



//What happens when 2 particles collide
void HumanManager::handle_collisions(Human& h1, Human& h2)
{
	
	int status; // Will hold the values of infected or not
	//0 = neither infected
	//1 = one of the infected
	//2 = both infected

	if (h1.getInfected() && h2.getInfected())
		status = 2;
	else 
		status = 1;
	

	if (status == 1) //dont run if both infected
	{
		int rand_num = rand() % 100; // create a random number to test for transimiton 
		/*
		if (h1.getInfected() == h2.getInfected())
		{
			//Calculate birth rate
			std::cout << "possible birth ";
			if (rand_num < b_rate)
				std::cout << "birth" << std::endl;
			std::cout << std::endl;
		}
		*/

		
		//if one has mask and other doesnt
		 if ((h1.getMask()  && !h2.getMask() )
			|| (!h1.getMask()  && h2.getMask() )) {
			int t_rate_1_mask = t_rate * (mask_eff / 100); //transmition rate * by the mask effiefficy %
			std::cout << "enter io";
			if (t_rate_1_mask)
			{
				std::cout << "Collision  with 1/0 mask" << std::endl;
				h1.setInfected(true);
				h2.setInfected(true);
				h1.setState(h1.area_);
				h2.setState(h2.area_);
			}
		}

		//if both have mask
		else if (h1.getMask() == true && h2.getMask() == true)
		{
			int t_rate_1_mask = t_rate * (mask_eff / 100) * (mask_eff /100);
			std::cout << "Enter mask coll" << std::endl;
			if (t_rate_1_mask >= rand_num)
			{
				std::cout << "Collision with mask" << std::endl;
				h1.setInfected(true);
				h2.setInfected(true);
				h1.setState(h1.area_);
				h2.setState(h2.area_);
			}
		}
		//If neither have mask 
		else if (h1.getMask() == false && h2.getMask() == false)
		{
			std::cout << "Enter no mask coll" << std::endl;
			if (t_rate >= rand_num)
			{
				std::cout << "Collision with no mask" << std::endl;
				h1.setInfected(true);
				h2.setInfected(true);
				h1.setState(h1.area_);
				h2.setState(h2.area_);
			}
		}
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

void HumanManager::clear() {
	v.clear();
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

