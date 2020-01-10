#include <SFML/Graphics.hpp>

int main()
{
	// Initialization
	sf::RenderWindow window(sf::VideoMode(800, 600), "GAME");
	window.setFramerateLimit(60);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	
	// Game loop
	while (window.isOpen())
	{
		// Event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Clean up
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Logic

		// Rendering
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}