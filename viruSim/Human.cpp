#include "Human.h"
#include <iostream>

sf::Color mask_color(62, 247, 226, 255);
sf::Color infect_color(0, 200, 30, 200);
sf::Color dead(30, 30, 30, 255);

//draw human
void Human::draw(sf::RenderWindow &wnd) {
	wnd.draw(circle);
}

//update human color based on state (infected or not)
//need to add additional cases and textures for masks. Will have 4 total.
void Human::update_color(float area) {
	switch (state) {
	case 0:
		circle.setFillColor(infect_color);
		break;
	case 1:
		circle.setFillColor(sf::Color::White);
		break;
	case 2:
		circle.setFillColor(infect_color);
		circle.setOutlineColor(mask_color);
		circle.setOutlineThickness(-r/3);
		break;
	case 3:
		circle.setFillColor(sf::Color::White);
		circle.setOutlineColor(mask_color);
		circle.setOutlineThickness(-r/3);
		break;
	case 4:
		circle.setFillColor(dead);
	}
}

//Update human position
void Human::update(sf::Time dt) {
	pos.x += vel.x*dt.asMicroseconds()/1000; //microseconds was rounding so i did this.
	pos.y += vel.y*dt.asMicroseconds()/1000;
	circle.setPosition(pos);
}

//If there is a wall, get negative velocity in the direction of wall hit
void Human::check_wall() {
	if (pos.x + r >= 860 || pos.x - r <= 30)
		vel.x *= -1;
	if (pos.y + r >= 860 || pos.y - r <= 30)
		vel.y *= -1;
}