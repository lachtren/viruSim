#pragma once
#include "SFMLbase.h"
#include <iostream>
/*
Human class takes care of all of the attributes of a single Human.

MOST OF THIS CLASS IS HARDCODED FOR TESTING PURPOSES
eventually most of the member variables of human will be randomly generated.
*/

class Human
{
	int age;
	int state;
	bool mask;
	bool deceased = false;
	bool infected;
	sf::Vector2f vel;
	sf::Vector2f pos;
	sf::CircleShape circle;
	
public:
	float r;
	Human(float area, sf::Vector2f vel_init, sf::Vector2f pos_init) {
		pos = pos_init;
		vel = vel_init/area;
		r = 1000 / (pow(area, 2));
		update_color(area);
		circle.setOrigin(r, r);
		circle.setRadius(r);
	}
	//need to implement set_pos() and set_vel()
	sf::Vector2f get_pos();
	void update_color(float);
	void update(sf::Time);
	void draw(sf::RenderWindow& wnd);
	void check_wall();
	void setState(int);
	void setMask(bool);
	void setInfected(bool);
};

