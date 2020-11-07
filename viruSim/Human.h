#pragma once
#include "SFMLbase.h"

/*
Human class takes care of all of the attributes of a single Human.
*/

class Human
{
	int age;
	int state = 1;
	bool mask;
	sf::Vector2f vel = sf::Vector2f(.1f,.1f);
	sf::Vector2f pos = sf::Vector2f(50.f,50.f);
	sf::CircleShape circle;

public:
	Human() {
		update_color();
		circle.setOrigin(50.f, 50.f);
		circle.setPosition(pos);
		circle.setRadius(50);
	}
	//need to implement set_pos() and set_vel()
	void set_pos();
	void set_vel();
	void update_color();
	void update();
	void draw(sf::RenderWindow& wnd);
};

