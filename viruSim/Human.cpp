#include "Human.h"
#include <iostream>

//draw human
void Human::draw(sf::RenderWindow &wnd) {
	wnd.draw(circle);
}

//update human color based on state (infected or not)
//need to add additional cases and textures for masks. Will have 4 total.
void Human::update_color() {
	switch (state) {
	case 0:
		circle.setFillColor(sf::Color::Green);
		break;
	case 1:
		circle.setFillColor(sf::Color::White);
		break;
	}
}

//Update human position
void Human::update() {
	pos.x += vel.x;
	pos.y += vel.y;
	circle.setPosition(pos);
}