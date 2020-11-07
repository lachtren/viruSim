#pragma once
#include "SFMLbase.h"
#include "Human.h"
#include "HumanManager.h"

class Sim
{
	static Sim* instance;
	Sim() {
	}
	sf::RenderWindow* wnd;
	HumanManager* hm;
public:
	static Sim* getInstance();
	void setup();
	void begin();
	
};

