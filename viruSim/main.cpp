#include "SFMLbase.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello World!");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(0xff, 0, 0xff, 0xff));
		window.display();
	}

	return 0;
}