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
	static Sim* instance;
	Sim() {
	}
	sf::RenderWindow* wnd;
	HumanManager* hm;
	sf::Clock clock;
public:
	static Sim* getInstance();
	void setup();
	void begin();
	
};

