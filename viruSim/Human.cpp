#include "Human.h"
#include <iostream>

//draw human
void Human::draw(sf::RenderWindow &wnd) {
	wnd.draw(circle);
}

//update human color based on state (infected or not)
//need to add additional cases and textures for masks. Will have 4 total.
void Human::update_color(float area) {
	switch (state) {
	case 0:
		circle.setFillColor(sf::Color::Green);
		circle.setOutlineColor(sf::Color::Black);
		break;
	case 1:
		circle.setFillColor(sf::Color::White);
		circle.setOutlineColor(sf::Color::Black);
		break;
	case 2:
		circle.setFillColor(sf::Color::Green);
		circle.setOutlineColor(sf::Color::Blue);
		circle.setOutlineThickness(-circle.getRadius());
		break;
	case 3:
		circle.setFillColor(sf::Color::White);
		circle.setOutlineColor(sf::Color(62,247,226,255));
		circle.setOutlineThickness(-r/3);
		break;
	}
}

//Update human position
void Human::update(sf::Time dt) {
	pos.x += vel.x*dt.asMicroseconds()/1000; //microseconds was rounding so i did this.
	pos.y += vel.y*dt.asMicroseconds()/1000;
	circle.setPosition(pos);
}