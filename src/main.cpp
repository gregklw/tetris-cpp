#include <SFML/Graphics.hpp>
#include "../header/TetrisPiece.h"
#include "../header/GameArea.h"
#include "../header/Cell.h"
#include "../header/GameInfo.h"

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project");
	window.setFramerateLimit(144);

	TetrisPiece testPiece(sf::Color::Green);

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

		//check if piece collides into anything


		dropTimer++;

		if (dropTimer > 10)
		{
			//testPiece.moveDown();
			dropTimer = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !gameArea.checkHorizontalCollision(testPiece, sf::Vector2f(1,0)))
		{
			testPiece.moveRight();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && !gameArea.checkHorizontalCollision(testPiece, sf::Vector2f(-1, 0)))
		{
			testPiece.moveLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			if (!gameArea.checkVerticalCollision(testPiece))
			{
				testPiece.moveDown();
			}
			else
			{
				gameArea.occupyCells(testPiece);
			}
		}

		window.clear();

		gameArea.update(window);
		testPiece.update(window);

		window.display();
	}
}
