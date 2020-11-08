#include "Sim.h"
#include <iostream>
#include <random>
#include <math.h>
#define PI 3.141592
HumanManager* HumanManager::instance = 0;


//This can be cleaned up. Draws arena and grid lines
void draw_arena(sf::RenderWindow& wnd, float width) {
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

	sf::RectangleShape outline(sf::Vector2f(230, 430));
	outline.setPosition(sf::Vector2f(920.f, 70.f));
	outline.setFillColor(sf::Color(40, 40, 40, 40));
	outline.setOutlineColor(sf::Color(200, 200, 200, 200));
	outline.setOutlineThickness(10);
	wnd.draw(outline);
}

//Instantiate Sim singleton. This is in replace of constructor.
Sim* Sim::getInstance() {
	if (!instance) {
		instance = new Sim;
	}
	return instance;
}

//fills hm with humans
void fill_hm(HumanManager*hm, float r, int pop_init, int infected_init, int mask_percent, float width) {
	for (int i = 0; i < pop_init-infected_init; i++) {
		int v_deg = rand() % 360 + 1;
		int rand_dist = 8000 - r * 10;
		auto pos = sf::Vector2f((static_cast<float>((rand() % rand_dist + 300 + r * 10)) / 10.), static_cast<float>(rand() % rand_dist + 300 + r * 10) / 10);
		auto veloc = sf::Vector2f(cos(v_deg * PI / 180), sin(v_deg * PI / 180));
		Human h(width, veloc, pos);
		int mask = rand() % 100 + 0;
		h.setMask(mask < mask_percent);
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
		h.setMask(mask < mask_percent);
		h.setInfected(1);
		h.setState(width);
		hm->push_back(h);
	}
}


void Sim::load_params() {
	params.setPosition(sf::Vector2f(965.f, 75.f));
	params.setFont(font);
	params.setString("Parameters");
	params.setCharacterSize(30);
	params.setFillColor(sf::Color::White);
	p_v.push_back(params);
	params.setCharacterSize(20);
	params.setString("Community Size: " + std::to_string(static_cast<int>(width)) + "X" + std::to_string(static_cast<int>(width)));
	params.setPosition(940.f, 125.f);
	p_v.push_back(params);
	params.setString("Transmission Rate: " + std::to_string(t_rate) + "%");
	params.setPosition(940.f, 150.f);
	p_v.push_back(params);
	params.setString("Mask Wearers: " + std::to_string(mask_percent) + "%");
	params.setPosition(940.f, 175.f);
	p_v.push_back(params);
	params.setString("Initial Population: " + std::to_string(pop_init));
	params.setPosition(940.f, 200.f);
	p_v.push_back(params);
	params.setString("Initial Infected: " + std::to_string(infected_init));
	params.setPosition(940.f, 225.f);
	p_v.push_back(params);
	params.setString("Mask effectiveness " + std::to_string(mask_percent) + "%");
	params.setPosition(940.f, 250.f);
	p_v.push_back(params);
}

void Sim::load_stats() {
	stats.setPosition(sf::Vector2f(985.f, 300.f));
	stats.setFont(font);
	stats.setString("Stats");
	stats.setCharacterSize(30);
	stats.setFillColor(sf::Color::White);
	s_v.push_back(stats);
	stats.setCharacterSize(20);
	stats.setPosition(940.f, 350.f);
	s_v.push_back(stats);
	stats.setPosition(940.f, 375.f);
	s_v.push_back(stats);
	stats.setPosition(940.f, 400.f);
	s_v.push_back(stats);
	stats.setPosition(940.f, 425.f);
	s_v.push_back(stats);
	stats.setPosition(940.f, 450.f);
	s_v.push_back(stats);
}


//Create window and instantiate HumanManager
//For testing purposes, creates a human and puts it into hm
void Sim::setup() {
	srand(time(NULL));
	wnd = new sf::RenderWindow(sf::VideoMode(1200, 900), "ViruSim", sf::Style::Close);
	hm = hm->getInstance();
	float r = 1000 / (pow(width, 2));
	fill_hm(hm, r, pop_init, infected_init, mask_percent, width);
	if (!font.loadFromFile("Assets/Oswald-VariableFont_wght.ttf")) {
	}
	load_params();
	load_stats();
}

void display_text(sf::RenderWindow& wnd, std::vector<sf::Text> p_v, std::vector<sf::Text> s_v) {
	
	for (int i = 0; i < p_v.size(); i++)
		wnd.draw(p_v[i]);
	for (int i = 0; i < s_v.size(); i++)
		wnd.draw(s_v[i]);
}

void Sim::update_stats(sf::Time dt) {
	stats_timer -= dt.asMicroseconds() * 1000;
	if (stats_timer <= 0) {
		num_inf = hm->count_inf();
		healthy = hm->population() - num_inf;
		population = hm->population();
		infected_rate = static_cast<double>(num_inf) / static_cast<double>(hm->population())*100;
		s_v[1].setString("Current population: " + std::to_string(population));
		s_v[2].setString("Healthy: " + std::to_string(healthy));
		s_v[3].setString("Infected: " + std::to_string(num_inf));
		s_v[4].setString("% Infected: " + std::to_string(infected_rate));
		s_v[5].setString("Deceased: " + std::to_string(deceased));
		stats_timer = 250;
	}
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
		hm->check_collision();
		update_stats(dt);
		//load_stats();
		wnd->clear(sf::Color(0, 0, 0, 0xff));
		draw_arena(*wnd, width);
		hm->draw(*wnd);
		display_text(*wnd, p_v, s_v);
		wnd->display();

		
	}
}