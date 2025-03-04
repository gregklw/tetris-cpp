#include <SFML/Graphics.hpp>
#include "../header/TetrisPiece.h"
#include "../header/GameArea.h"
#include "../header/Cell.h"
#include "../header/GameInfo.h"
#include "../header/GameController.h"

extern std::vector<TetrisPiece> tetraminoList;
extern int dropTimerCooldown;
extern int sensitivityCooldown;

TetrisPiece testPiece = tetraminoList[std::rand() % tetraminoList.size()];
GameArea gameArea = GameArea();
GameController gameController = GameController();

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 1280u, 720u }), "CMake SFML Project");
	window.setFramerateLimit(144);

	bool hardDroppedOnPress = false;
	bool rotateOnPress = false;

	int dropTimer = 0;
	int sensitivityTimer = 0;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
				{
					gameController.rotatePiece(testPiece, gameArea);
					gameController.rotateOnPress = true;
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
				{
					gameController.hardDropPiece(testPiece, gameArea);
					gameController.hardDroppedOnPress = true;
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
				{
					gameController.movePieceLeft(testPiece, gameArea);
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
				{
					gameController.movePieceRight(testPiece, gameArea);
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
				{
					gameController.movePieceDown(testPiece, gameArea);
				}
			}

			if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				if (keyReleased->scancode == sf::Keyboard::Scancode::Up)
				{
					gameController.rotateOnPress = false;
				}

				if (keyReleased->scancode == sf::Keyboard::Scancode::Space)
				{
					gameController.hardDroppedOnPress = false;
				}
			}
		}

		sf::Time t1 = sf::milliseconds(50);
		sf::sleep(t1);

		//check if piece collides into anything

		dropTimer++;
		sensitivityTimer++;

		if (dropTimer > dropTimerCooldown)
		{
			gameController.movePieceDown(testPiece, gameArea);
			dropTimer = 0;
		}

		if (sensitivityTimer > sensitivityCooldown)
		{
			
			sensitivityTimer = 0;
		}

		window.clear();

		gameArea.update(window);
		gameArea.previewHardDrop(window, testPiece);
		testPiece.update(window);

		window.display();
	}
}
