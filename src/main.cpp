#include <SFML/Graphics.hpp>
#include "../header/TetrisPiece.h"
#include "../header/GameArea.h"
#include "../header/Cell.h"
#include "../header/GameInfo.h"
#include "../header/GameController.h"
#include "../header/GameUI.h"

extern std::vector<TetrisPiece> tetraminoList;
extern int dropTimerCooldown;
extern int sensitivityCooldown;
extern sf::Vector2f gameAreaStartPosition;
extern bool holdPieceOnPress;
extern bool hardDroppedOnPress;
extern bool rotateOnPress;

GameArea gameArea = GameArea(gameAreaStartPosition);
TetrisPiece currentPiece = getNewPiece();
GameController gameController = GameController();

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 1280u, 720u }), "CMake SFML Project");
	window.setFramerateLimit(144);

	int dropTimer = 0;
	int sensitivityTimer = 0;

	init();

	currentPiece.setScreenPosition(gameAreaStartPosition);

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
					gameController.rotatePiece(currentPiece, gameArea);
					rotateOnPress = true;
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
				{
					gameController.hardDropPiece(currentPiece, gameArea);
					hardDroppedOnPress = true;
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
				{
					gameController.movePieceLeft(currentPiece, gameArea);
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
				{
					gameController.movePieceRight(currentPiece, gameArea);
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
				{
					gameController.movePieceDown(currentPiece, gameArea);
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::RShift)
				{
					
					gameController.holdPiece(currentPiece, gameArea);
					holdPieceOnPress = true;
				}
			}

			if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				if (keyReleased->scancode == sf::Keyboard::Scancode::Up)
				{
					rotateOnPress = false;
				}

				if (keyReleased->scancode == sf::Keyboard::Scancode::Space)
				{
					hardDroppedOnPress = false;
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
			gameController.movePieceDown(currentPiece, gameArea);
			dropTimer = 0;
		}

		if (sensitivityTimer > sensitivityCooldown)
		{
			
			sensitivityTimer = 0;
		}

		window.clear();

		gameArea.update(window);
		gameArea.previewHardDrop(window, currentPiece);
		currentPiece.update(window);
		displayGameUI(window);

		window.display();
	}
}
