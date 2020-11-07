#include "Human.h"
#include <iostream>

void Human::draw(sf::RenderWindow &wnd) {
	wnd.draw(circle);
}

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

void Human::update() {
	pos.x += vel.x;
	pos.y += vel.y;
	circle.setPosition(pos);
}