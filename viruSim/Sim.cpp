#include "Sim.h"

HumanManager* HumanManager::instance = 0;

//Instantiate Sim singleton. This is in replace of constructor.
Sim* Sim::getInstance() {
	if (!instance) {
		instance = new Sim;
	}
	return instance;
}

//Create window and instantiate HumanManager
//For testing purposes, creates a human and puts it into hm
void Sim::setup() {
	wnd = new sf::RenderWindow(sf::VideoMode(900, 900), "ViruSim", sf::Style::Close);
	hm = hm->getInstance();
	Human h;
	hm->push_back(h);
}

//Begin main simulation loop
void Sim::begin() {
	Human h;
	while (wnd->isOpen())
	{
		sf::Event event;
		while (wnd->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				wnd->close();
		}
		wnd->clear(sf::Color(0, 30, 30, 0xff));
		hm->update();
		hm->draw(*wnd);
		wnd->display();
	}
}