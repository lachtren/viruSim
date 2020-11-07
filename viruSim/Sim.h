#pragma once
#include "SFMLbase.h"
#include "Human.h"
#include "HumanManager.h"
/*
Sim class does all heavy lifting of the simulation.
Renders objects, handles control of time and parameters once implemented
*/
class Sim
{
	float width;
	int pop_init;
	int infected_init;
	int mask_percent;
	static Sim* instance;
	Sim() {
		std::cout << "Width of community: ";
		std::cin >> width;
		std::cout << "Initial population: ";
		std::cin >> pop_init;
		std::cout << "Initial infected: ";
		std::cin >> infected_init;
		std::cout << "Percent of mask wearers: ";
		std::cin >> mask_percent;
	}
	sf::RenderWindow* wnd;
	HumanManager* hm;
	sf::Clock clock;



public:
	static Sim* getInstance();
	void setup();
	void begin();
	
};