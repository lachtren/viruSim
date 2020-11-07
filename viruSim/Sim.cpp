#include "Sim.h"
#include <iostream>
#include <random>
#include <math.h>
#define PI 3.141592
HumanManager* HumanManager::instance = 0;

float width = 10; //width/height of arena. Everything scales off of this.
int age_of_transmission = 6; //not been implemented, not sure if i will.
int pop_init = 10;
int infected_init = 1;
int mask_percent = 50;

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

//fills hm with humans
void fill_hm(HumanManager*hm, float r) {
	for (int i = 0; i < pop_init-infected_init; i++) {
		int v_deg = rand() % 360 + 1;
		int rand_dist = 8000 - r * 10;
		auto pos = sf::Vector2f((static_cast<float>((rand() % rand_dist + 300 + r * 10)) / 10.), static_cast<float>(rand() % rand_dist + 300 + r * 10) / 10);
		auto veloc = sf::Vector2f(cos(v_deg * PI / 180), sin(v_deg * PI / 180));
		Human h(width, veloc, pos);
		int mask = rand() % 100 + 0;
		h.setMask(mask > mask_percent);
		h.setInfected(0);
		h.setState(width);
		hm->push_back(h);
	}
	for (int i = 0; i < infected_init; i++) {
		int v_deg = rand() % 360 + 1;
		int rand_dist = 8000 - r * 10;
		auto pos = sf::Vector2f((static_cast<float>((rand() % rand_dist + 300 + r * 10)) / 10.), static_cast<float>(rand() % rand_dist + 300 + r * 10) / 10);
		auto veloc = sf::Vector2f(cos(v_deg * PI / 180), sin(v_deg * PI / 180));
		Human h(width, veloc, pos);
		int mask = rand() % 100 + 0;
		h.setMask(mask > mask_percent);
		h.setInfected(1);
		h.setState(width);
		hm->push_back(h);
	}
}

//Create window and instantiate HumanManager
//For testing purposes, creates a human and puts it into hm
void Sim::setup() {
	srand(time(NULL));
	wnd = new sf::RenderWindow(sf::VideoMode(1200, 900), "ViruSim", sf::Style::Close);
	hm = hm->getInstance();
	float r = 1000 / (pow(width, 2));
	fill_hm(hm, r);
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
