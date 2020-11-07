#pragma once
#include "SFMLbase.h"
#include <iostream>
/*
Human class takes care of all of the attributes of a single Human.
*/

class Human
{
	int age;
	int state = 3;
	bool mask;
	sf::Vector2f vel = sf::Vector2f(1.f,1.f);
	sf::Vector2f pos = sf::Vector2f(50.f,50.f);
	sf::CircleShape circle;
	float r;
public:
	Human(float area) {
		r = 1000 / (pow(area, 2));
		update_color(area);
		circle.setOrigin(50.f, 50.f);
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
};

