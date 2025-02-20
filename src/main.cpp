#include <SFML/Graphics.hpp>
#include "../header/TetrisPiece.h"

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project");
	window.setFramerateLimit(144);

	float blockSize = 50;

	std::vector<TetrisBlock> blocks = {
		TetrisBlock(sf::Vector2f(0, 0),  sf::Color::Green),
		TetrisBlock(sf::Vector2f(0, 50), sf::Color::Green),
		TetrisBlock(sf::Vector2f(0, 100), sf::Color::Green),
		TetrisBlock(sf::Vector2f(0, 150), sf::Color::Green)
	};

	TetrisPiece testPiece(blocks);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			// left key is pressed: move our character
			testPiece.movePiece(sf::Vector2f(50, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			// left key is pressed: move our character
			testPiece.movePiece(sf::Vector2f(0, -50));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			// left key is pressed: move our character
			testPiece.movePiece(sf::Vector2f(0, 50));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			// left key is pressed: move our character
			testPiece.movePiece(sf::Vector2f(-50, 0));
		}

		window.clear();

		testPiece.update(window);

		window.display();
	}
}
