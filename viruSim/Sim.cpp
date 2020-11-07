#include "Sim.h"
#include <iostream>
HumanManager* HumanManager::instance = 0;

float width = 12; //width/height of arena. Everything scales off of this.
int age_of_transmission = 6; //not been implemented, not sure if i will.

//This can be cleaned up. Draws arena and grid lines
void draw_arena(sf::RenderWindow& wnd) {
	sf::RectangleShape arena(sf::Vector2f(830.f, 830.f));
	arena.setPosition(30, 30);
	arena.setFillColor(sf::Color(0, 20, 20, 20));
	arena.setOutlineColor(sf::Color(200, 200, 200, 200));
	arena.setOutlineThickness(10);
	wnd.draw(arena);
	float line_dist = 830 / width;
	for (int i = 30+line_dist; i < 800; i += line_dist) {
		sf::RectangleShape line(sf::Vector2f(2., 830));
		line.setFillColor(sf::Color(30,30,30,100));
		line.setPosition(i, 30);
		wnd.draw(line);
	}
	for (int i = 30 + line_dist; i < 800; i += line_dist) {
		sf::RectangleShape line(sf::Vector2f(830, 2.));
		line.setFillColor(sf::Color(30, 30, 30, 100));
		line.setPosition(30, i);
		wnd.draw(line);
	}
}

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
	wnd = new sf::RenderWindow(sf::VideoMode(1200, 900), "ViruSim", sf::Style::Close);
	hm = hm->getInstance();
	Human h(width);
	hm->push_back(h);
}

//Begin main simulation loop
void Sim::begin() {
	while (wnd->isOpen())
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (wnd->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				wnd->close();
		}
		hm->update(dt);
		wnd->clear(sf::Color(0, 0, 0, 0xff));
		draw_arena(*wnd);
		hm->draw(*wnd);
		wnd->display();
	}
}
