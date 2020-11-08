#include "Human.h"
#include <iostream>

sf::Color mask_color(0, 247, 30, 255);
sf::Color infect_color(200, 0, 30, 255);
sf::Color dead(30, 30, 30, 255);
const int window_size = 800; //830x830 that starts at 30x30
//int width = 9; //Link with one in human.h at somepoint
//int r = (1000 / (pow(width, 2))); // link with one in human.h
//int num_of_sections = window_size / r; //TODO: get area and replace 12 with a var

//draw human
void Human::draw(sf::RenderWindow &wnd)
{
	wnd.draw(circle);
}




//update human color based on state (infected or not)
//need to add additional cases and textures for masks. Will have 4 total.
void Human::update_color(float area)
{
	switch (state)
	{
	case 0:
		circle.setFillColor(infect_color);
		break;
	case 1:
		circle.setFillColor(sf::Color::White);
		break;
	case 2:
		circle.setFillColor(infect_color);
		circle.setOutlineColor(mask_color);
		circle.setOutlineThickness(-r / 3);
		break;
	case 3:
		circle.setFillColor(sf::Color::White);
		circle.setOutlineColor(mask_color);
		circle.setOutlineThickness(-r / 3);
		break;
	case 4:
		circle.setFillColor(dead);
	}
}

//Update human position
void Human::update(sf::Time dt)
{
	if (colliding == false) {
		pos.x += vel.x * dt.asMicroseconds() / 1000; //microseconds was rounding so i did this.
		pos.y += vel.y * dt.asMicroseconds() / 1000;
		circle.setPosition(pos);
		update_section();
	}
}

void Human::death(int f_rate) {
	int rand_num = rand() % 100000;
	if (infected) {
		if (rand_num < f_rate)
		{
			state = 4;
			update_color(area_);
			deceased = true;
			vel = sf::Vector2f(0, 0);
		}
	}
	
}

//If there is a wall, get negative velocity in the direction of wall hit
void Human::check_wall()
{
	if (pos.x + r >= 860)
	{
		vel.x *= -1;
		pos.x = 860 - r;
	}
	else if (pos.x - r <= 30)
	{
		pos.x = 30 + r;
		vel.x *= -1;
	}
	if (pos.y + r >= 860)
	{
		vel.y *= -1;
		pos.y = 860 - r;
	}
	else if (pos.y - r <= 30)
	{
		pos.y = 30 + r;
		vel.y *= -1;
	}
}

sf::Vector2f Human::get_pos()
{
	return pos;
}

void Human::update_section()
{
	int num_of_sections = window_size / r;
	//std::cout << num_of_sections << std::endl;
	for (int i = 1; i < num_of_sections+1; i++) {
		int left_bound = 30 + (i - 1) * window_size / num_of_sections;
		int right_bound = 30 + i * window_size / num_of_sections;
		if (pos.x >= left_bound && pos.x <= right_bound)
			section.first = i;
	}
	for (int i = 1; i < num_of_sections + 1; i++) {
		int upper_bound = 30 + (i - 1) * window_size / num_of_sections;
		int lower_bound = 30 + i * window_size / num_of_sections;
		if (pos.y >= upper_bound && pos.y <= lower_bound)
			section.second = i;
	}
	//std::cout << "Section first : " << section.first << ", section second" << section.second << std::endl;
}

void Human::update_colission(int dt) {
	collide_timer -= dt;
	if (collide_timer <= 0) {
		colliding = 0;
		colliding_cd = 1000;
		collide_timer = 2000;
	}
	else if (collide_timer <= 1250) {
		setState(area_);
		update_color(area_);
	}
}

void Human::setState(int area)
{
	if (infected && !mask)
		state = 0;
	else if (!infected && !mask)
		state = 1;
	else if (infected && mask)
		state = 2;
	else if (!infected && mask)
		state = 3;
	if (deceased)
		state = 4;
	update_color(area);
}

void Human::setMask(bool m)
{
	mask = m;
}

void Human::setInfected(bool i)
{
	infected = i;
}

bool Human::getInfected() {
	return infected;
}

bool Human::getMask() {
	return mask;
}