#pragma once
#include "SFMLbase.h"
#include <iostream>
#include <utility>
/*
Human class takes care of all of the attributes of a single Human.
*/

class Human
{
	int state;
	bool mask;
	bool deceased = false;
	int collide_timer = 2000;
	bool infected;
	sf::Vector2f vel;
	sf::Vector2f pos;
	sf::CircleShape circle;
	float area_;

public:
	std::pair<int, int> section;
	int width;
	float r;
	Human(float area, sf::Vector2f vel_init, sf::Vector2f pos_init)
	{
		pos = pos_init;
		area_ = area;
		vel = vel_init / area;
		r = 1000 / (pow(area, 2));
		update_color(area);
		circle.setOrigin(r, r);
		circle.setRadius(r);
	}
	int colliding_cd = 0;
	sf::Vector2f get_pos();
	bool colliding = false;
	void update_color(float);
	void update(sf::Time);
	void draw(sf::RenderWindow &wnd);
	void check_wall();
	void update_section();
	void setState(int);
	void setMask(bool);
	void setInfected(bool);
	bool getInfected();
	void update_colission(int);
	bool getMask();
};