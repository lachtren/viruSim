#include "Sim.h"


Sim* Sim::getInstance() {
	if (!instance) {
		instance = new Sim;
	}
	return instance;
}

void Sim::begin() {
	sf::RenderWindow wnd(sf::VideoMode(900, 900), "ViruSim", sf::Style::Close);
	Human h;
	while (wnd.isOpen())
	{
		sf::Event event;
		while (wnd.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				wnd.close();
		}

		wnd.clear(sf::Color(0, 30, 30, 0xff));
		h.update();
		h.draw(wnd);
		wnd.display();
	}
}