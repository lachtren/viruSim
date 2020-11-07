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
	int state = 4;
	bool mask;
	bool deceased = false;
	bool infected;
	sf::Vector2f vel = sf::Vector2f(.75f,.5f);
	sf::Vector2f pos = sf::Vector2f(120.f,120.f);
	sf::CircleShape circle;
	float r;
public:
	Human(float area) {
		r = 1000 / (pow(area, 2));
		update_color(area);
		circle.setOrigin(r, r);
		circle.setPosition(pos);
		circle.setRadius(r);
		vel = vel / area;
		std::cout << vel.x << " " << vel.y << std::endl;
	}
	//need to implement set_pos() and set_vel()
	void set_pos();
	void set_vel();
	void update_color(float);
	void update(sf::Time);
	void draw(sf::RenderWindow& wnd);
	void check_wall();
};

