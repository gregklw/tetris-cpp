#include <SFML/Graphics.hpp>
#include "../header/TetrisPiece.h"
#include "../header/GameArea.h"
#include "../header/Cell.h"
#include "../header/GameInfo.h"
#include "../header/GameUI.h"

extern const int dropTimerCooldown;
extern const int sensitivityCooldown;
extern const sf::Vector2f gameAreaPosition;
extern bool holdPieceOnPress;
extern bool hardDroppedOnPress;
extern bool rotateOnPress;

GameArea gameArea = GameArea(gameAreaPosition);

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 1280u, 720u }), "CMake SFML Project");
	window.setFramerateLimit(144);

	int sensitivityTimer = 0;

	initUI();
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
					gameArea.rotatePiece();
					rotateOnPress = true;
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
				{
					gameArea.hardDropCurrentPiece();
					hardDroppedOnPress = true;
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
				{
					gameArea.movePieceLeft();
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
				{
					gameArea.movePieceRight();
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
				{
					gameArea.moveCurrentPieceDown();
				}

				if (keyPressed->scancode == sf::Keyboard::Scancode::RShift)
				{

					gameArea.holdPiece();
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

		sensitivityTimer++;


		if (sensitivityTimer > sensitivityCooldown)
		{
			sensitivityTimer = 0;
		}

		window.clear();
		gameArea.update(window);
		gameArea.previewHardDrop(window);
		displayGameUI(window);

		window.display();
	}
}
