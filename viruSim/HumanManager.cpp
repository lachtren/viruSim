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
	std::cout << v.size() << std::endl;
	for (auto i = v.begin(); i != v.end(); i++)
	{
		i->check_wall();
		i->update_section();
		i->update(dt);
		i->death(f_rate);
	}
}

//Update the variables for the the collison deteection
void HumanManager::store_all_vars(int sim_t_rate,
	int sim_mask_eff,
	int sim_f_rate,
	int sim_b_rate,
	int sim_m_rate) {
	m_rate = sim_m_rate;
	t_rate = sim_t_rate;
	mask_eff = sim_mask_eff;
	f_rate = sim_f_rate;
	b_rate = sim_b_rate;
}



//What happens when 2 particles collide
void HumanManager::handle_collisions(std::vector<Human>::iterator h1, std::vector<Human>::iterator h2)
{
	
	int status; // Will hold the values of infected or not
	//0 = one is dead
	//1 = one of the infected
	//2 = both infected

	if (h1->getInfected() && h2->getInfected())
		status = 2;
	else if (h1->deceased || h2->deceased) {
		status = 0;
	}
	else 
		status = 1;
	

	if (status == 1) //dont run if both infected
	{
		int rand_num = rand() % 100; // create a random number to test for transimiton 
		
		if (h1->getInfected() == h2->getInfected())
		{
			if (rand_num < b_rate) {
				babies++;
			}
				
		}
		else {


			//if one has mask and other doesnt
			if ((h1->getMask() && !h2->getMask())
				|| (!h1->getMask() && h2->getMask())) {
				//std::cout << mask_eff << std::endl;
				double  t_rate_1_mask = t_rate * ((100 - mask_eff) / 100.0);
				//transmition rate * by the mask effiefficy %
				//std::cout << t_rate << std::endl;
				//std::cout << t_rate_1_mask << std::endl;

				if (rand_num < t_rate_1_mask)
				{
					h1->setInfected(true);
					h2->setInfected(true);
					h1->setState(h1->area_);
					h2->setState(h2->area_);
				}
			}

			//if both have mask
			else if (h1->getMask() == true && h2->getMask() == true)
			{
				double t_rate_2_mask = t_rate * ((100 - mask_eff) / 100.0) * ((100 - mask_eff) / 100.0);
				//std::cout << t_rate_2_mask << std::endl;
				//std::cout << rand_num << ": " << t_rate_2_mask << std::endl;
				if (rand_num < t_rate_2_mask)
				{
					//std::cout << "masked collision with transmit" << std::endl;
					h1->setInfected(true);
					h2->setInfected(true);
					h1->setState(h1->area_);
					h2->setState(h2->area_);
				}
			}
			//If neither have mask 
			else if (h1->getMask() == false && h2->getMask() == false)
			{
				if (t_rate >= rand_num)
				{
					h1->setInfected(true);
					h2->setInfected(true);
					h1->setState(h1->area_);
					h2->setState(h2->area_);
				}
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
				if (!(itr->deceased || itr_2->deceased))
				{
					if (itr->colliding_cd <= 0 && itr_2->colliding_cd <= 0) {
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


									handle_collisions(itr, itr_2); //Reference of the human object

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
		for (int i = 0; i < babies; i++) {
			int v_deg = rand() % 360 + 1;
			int rand_dist = 8000 - v[0].r * 10;
			auto pos = sf::Vector2f((static_cast<float>((rand() % rand_dist + 300 + v[0].r * 10)) / 10.), static_cast<float>(rand() % rand_dist + 300 + v[0].r * 10) / 10);
			auto veloc = sf::Vector2f(cos(v_deg * 3.14 / 180), sin(v_deg * 3.14 / 180));
			Human h(v[0].area_, veloc, pos);
			int mask = rand() % 100 + 0;
			h.setMask(mask < m_rate);
			h.setInfected(0);
			h.setState(v[0].area_);
			v.push_back(h);
		}
		babies = 0;
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

