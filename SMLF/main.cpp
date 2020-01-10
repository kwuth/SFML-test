#include <SFML/Graphics.hpp>
#include <iostream>

bool keyPressed(sf::Event event, sf::Keyboard::Key key) {
	return event.type == sf::Event::KeyPressed && event.key.code == key;
}

bool keyReleased(sf::Event event, sf::Keyboard::Key key) {
	return event.type == sf::Event::KeyReleased && event.key.code == key;
}

int main()
{
	// Initialization
	sf::RenderWindow window(sf::VideoMode(800, 600), "GAME");
	window.setFramerateLimit(60);

	window.setKeyRepeatEnabled(false);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	
	sf::Event event;

	bool aPressed = false;
	bool aReleased = false;
	bool space = false;

	// Game loop
	while (window.isOpen())
	{
		// Event
		while (window.pollEvent(event))
		{
			if (keyPressed(event, sf::Keyboard::A)) {
				aPressed = true;
			}

			if (keyReleased(event, sf::Keyboard::A)) {
				aReleased = true;
			}

			if (keyPressed(event, sf::Keyboard::Space)) {
				space = !space;
			}

			// Clean up
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		// Logic
		if (aPressed) {
			std::cout << "The A key has been pressed\n";
			aPressed = false;
		}

		if (aReleased) {
			std::cout << "The A key has been released\n";
			aReleased = false;
		}

		if (space) {
			std::cout << "SPACE\n";
		}

		if (space == false) {
			std::cout << "NOT SPACE\n";
		}

		// Rendering
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}