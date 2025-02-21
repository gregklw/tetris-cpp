#include <SFML/Graphics.hpp>
#include "../header/TetrisPiece.h"
#include "../header/GameArea.h"
#include "../header/GameInfo.h"

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project");
	window.setFramerateLimit(144);

	std::array<TetrisBlock, 4> blocks = {
		TetrisBlock(sf::Vector2f(0, 0),  sf::Color::Green),
		TetrisBlock(sf::Vector2f(0, 50), sf::Color::Green),
		TetrisBlock(sf::Vector2f(0, 100), sf::Color::Green),
		TetrisBlock(sf::Vector2f(0, 150), sf::Color::Green)
	};

	TetrisPiece testPiece(blocks);

	GameArea gameArea = GameArea();

	int dropTimer = 0;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		sf::Time t1 = sf::milliseconds(50);
		sf::sleep(t1);

		dropTimer++;

		if (dropTimer > 10)
		{
			testPiece.movePiece(sf::Vector2f(0, blockSize));
			dropTimer = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			// left key is pressed: move our character
			testPiece.movePiece(sf::Vector2f(blockSize, 0));
		}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		//{
		//	// left key is pressed: move our character
		//	testPiece.movePiece(sf::Vector2f(0, -blockSize));
		//}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			// left key is pressed: move our character
			testPiece.movePiece(sf::Vector2f(0, blockSize));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			// left key is pressed: move our character
			testPiece.movePiece(sf::Vector2f(-blockSize, 0));
		}

		window.clear();

		gameArea.update(window);
		testPiece.update(window);

		window.display();
	}
}
