#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>


int main()
{
	// Initialization
	sf::RenderWindow window(sf::VideoMode(800, 600), "GAME");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Event event;

	// Font
	sf::Font font;
	if (!font.loadFromFile("Assets/fonts/FiraCode-Regular.ttf")) {
		return -1;
	}

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::Red);
	score.setPosition(380, 10);
	score.setString("0 : 0");

	// Textures
	sf::Texture tex_pad;
	sf::Texture tex_ball;
	sf::Texture tex_background;

	if (!tex_pad.loadFromFile("Assets/images/pad.png")) {
		return -1;
	}

	if (!tex_ball.loadFromFile("Assets/images/ball.png")) {
		return -1;
	}

	if (!tex_background.loadFromFile("Assets/images/background.png")) {
		return -1;
	}
	// Sounds
	sf::SoundBuffer buffer_hit;
	if (!buffer_hit.loadFromFile("Assets/sounds/hit.wav")) {
		return -1;
	}

	sf::Sound hit;
	hit.setBuffer(buffer_hit);

	// States
	bool up = false, down = false;

	// Variables
	int yVelocityPad1 = 0;
	int xVelocityBall = -4, yVelocityBall = -4;
	int yVelocityPad2 = 0;
	int pad1Score = 0;
	int pad2Score = 0;

	/////// Shapes
	// Background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f((float)800, (float)600));
	background.setPosition(0, 0);
	background.setTexture(&tex_background);
	// Pad1
	sf::RectangleShape pad1;
	pad1.setSize(sf::Vector2f(50, 100));
	pad1.setPosition(50, 200);
	pad1.setTexture(&tex_pad);

	// Pad2
	sf::RectangleShape pad2;
	pad2.setSize(sf::Vector2f(50, 100));
	pad2.setPosition(700, 200);
	pad2.setTexture(&tex_pad);

	// Ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(50, 50));
	ball.setPosition(400, 200);
	ball.setTexture(&tex_ball);

	// Game loop
	while (window.isOpen())
	{
		// Event
		while (window.pollEvent(event))
		{
			// Clean up
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();

			// Key Pressed
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				up = true;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
				down = true;
			}
			// Key Released
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
				up = false;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
				down = false;
			}
		}

		////// Logic
		// Pad1
		if (up) {
			yVelocityPad1 = -5;
		}

		if (down) {
			yVelocityPad1 = 5;
		}

		if ((up && down) || (!up && !down)) {
			yVelocityPad1 = 0;
		}

		pad1.move(0, yVelocityPad1);
		
		// Out of Bounds Check
		if (pad1.getPosition().y < 0) {
			pad1.setPosition(50, 0);
		}
		else if (pad1.getPosition().y > window.getSize().y - pad1.getSize().y) {
			// El tamaño de la pantalla menos los 100 de altura del pad
			pad1.setPosition(50, window.getSize().y - pad1.getSize().y);
		}

		// Pad2
		if (ball.getPosition().y < pad2.getPosition().y) {
			yVelocityPad2 = -2;
		}

		if (ball.getPosition().y > pad2.getPosition().y) {
			yVelocityPad2 = 2;
		}

		pad2.move(0, yVelocityPad2);

		// Out of Bounds Check
		if (pad2.getPosition().y < 0) {
			pad2.setPosition(700, 0);
		}
		else if (pad2.getPosition().y > window.getSize().y - pad2.getSize().y) {
			// El tamaño de la pantalla menos los 100 de altura del pad
			pad2.setPosition(700, window.getSize().y - pad2.getSize().y);
		}


		// Ball
		// Out of Bounds Check
		if (ball.getPosition().y < 0) {
			yVelocityBall = -yVelocityBall;
		} else if (ball.getPosition().y > window.getSize().y - ball.getSize().y) {
			yVelocityBall = -yVelocityBall;
		}

		if (ball.getPosition().x < 0) {
			ball.setPosition(400, 200);
			xVelocityBall = 4;
			yVelocityBall = -4;
			pad2Score++;
		} else if (ball.getPosition().x > window.getSize().x - ball.getSize().x) {
			ball.setPosition(400, 200);
			xVelocityBall = -4;
			yVelocityBall = 4;
			pad1Score++;
		}
		ball.move(xVelocityBall, 0);
		// Collition Detection
		if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds())) {
			xVelocityBall = -xVelocityBall;
			ball.move(xVelocityBall, 0);
			hit.play();
		}

		if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds())) {
			xVelocityBall = -xVelocityBall;
			ball.move(xVelocityBall, 0);
			hit.play();
		}


		ball.move(0, yVelocityBall);
		if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds())) {
			yVelocityBall = -yVelocityBall;
			ball.move(0, yVelocityBall);
			hit.play();
		}

		if (ball.getGlobalBounds().intersects(pad2.getGlobalBounds())) {
			yVelocityBall = -yVelocityBall;
			ball.move(0, yVelocityBall);
			hit.play();
		}

		// Rendering
		window.clear();
		window.draw(background);
		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);
		// Score
		std::stringstream text;
		text << pad1Score << " : " << pad2Score;
		score.setString(text.str());
		window.draw(score);
		window.display();
	}

	return 0;
}