#include "Human.h"
#include <iostream>

sf::Color mask_color(0, 247, 30, 255);
sf::Color infect_color(200, 0, 30, 255);
sf::Color dead(30, 30, 30, 255);
const int num_of_sections = 10;
const int window_size = 800; //830x830 that starts at 30x30
int section;
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
	pos.x += vel.x * dt.asMicroseconds() / 1000; //microseconds was rounding so i did this.
	pos.y += vel.y * dt.asMicroseconds() / 1000;
	circle.setPosition(pos);
	update_section();
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
	int area_incriment = window_size / num_of_sections;						 //Size of each section
	int adjustment_for_window_corner = 30;									 //Due to the fact that the area is 830x830 and not 800x800
	for (auto first_y_bound = 0, second_y_bound = area_incriment, count = 0; //Create y bounds for each section
		 first_y_bound < window_size; first_y_bound += area_incriment,
			  second_y_bound += area_incriment, count++)
	{
		for (auto first_x_bound = 0, second_x_bound = area_incriment; // Create x bounds of each section
			 first_x_bound < window_size;
			 first_x_bound += area_incriment, second_x_bound += area_incriment)
		{
			//Check if the human is within the sqare
			if (pos.x - adjustment_for_window_corner >= first_x_bound &&
				pos.x - adjustment_for_window_corner <= second_x_bound &&
				pos.y - adjustment_for_window_corner >= first_y_bound &&
				pos.y - adjustment_for_window_corner <= second_y_bound)
			// if it is within the current section assign it to that section
			{
				section = count;
				break; //Becasue we found the section we can leave
			}
		} //End of x bounds loop
		if (section == count)
			break; //Leave loop if we already found the section number

	} //end of y bounds loop
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