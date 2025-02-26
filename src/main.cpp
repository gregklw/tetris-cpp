#include <SFML/Graphics.hpp>
#include "../header/TetrisPiece.h"
#include "../header/GameArea.h"
#include "../header/Cell.h"
#include "../header/GameInfo.h"

extern std::vector<TetrisPiece> tetraminoList;

TetrisPiece testPiece = tetraminoList[std::rand() % tetraminoList.size()];
GameArea gameArea = GameArea();
void checkLandedOnPieceBelow();
void hardDrop();
void rotateShape();

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 1280u, 720u }), "CMake SFML Project");
	window.setFramerateLimit(144);

	bool hardDroppedOnPress = false;
	bool rotateOnPress = false;

	int dropTimer = 0;

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
				if (keyPressed->scancode == sf::Keyboard::Scan::Space && !hardDroppedOnPress)
				{
					hardDroppedOnPress = true;
					hardDrop();
				}

				if (keyPressed->scancode == sf::Keyboard::Scan::Up && !rotateOnPress)
				{
					rotateOnPress = true;
					rotateShape();
				}
			}

			if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				if (keyReleased->scancode == sf::Keyboard::Scan::Space)
				{
					hardDroppedOnPress = false;
				}
				if (keyReleased->scancode == sf::Keyboard::Scan::Up)
				{
					rotateOnPress = false;
				}
			}

		}
		sf::Time t1 = sf::milliseconds(50);
		sf::sleep(t1);

		//check if piece collides into anything

		dropTimer++;

		if (dropTimer > 10)
		{
			checkLandedOnPieceBelow();
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
			checkLandedOnPieceBelow();
		}

		window.clear();

		gameArea.update(window);
		testPiece.update(window);

		window.display();
	}
}

void checkLandedOnPieceBelow()
{
	if (!gameArea.checkVerticalCollision(testPiece))
	{
		testPiece.moveDown();
	}
	else
	{
		gameArea.occupyCells(testPiece);
		int lowestRowToStart = 0;

		for (int i = 0; i < testPiece.blocks.size(); i++)
		{
			int yPos = testPiece.blocks[i].getBlockPosition().y;
			if (lowestRowToStart < yPos)
			{
				lowestRowToStart = yPos;
			}
		}

		std::cout << lowestRowToStart << " Lowest Row \n";

		gameArea.checkAndClearRow(lowestRowToStart);
		testPiece = gameArea.getNewPiece();
	}
}

void hardDrop()
{
	while (!gameArea.checkVerticalCollision(testPiece))
	{
		testPiece.moveDown();
	}
	gameArea.occupyCells(testPiece);
	int lowestRowToStart = gameAreaDimensions.y - 1;
	for (int i = 0; testPiece.blocks.size(); i++)
	{
		int yPos = testPiece.blocks[i].getBlockPosition().y;
		if (lowestRowToStart > yPos)
		{
			lowestRowToStart = yPos;
		}
	}
	gameArea.checkAndClearRow(lowestRowToStart);
	testPiece = gameArea.getNewPiece();
}

void rotateShape()
{
	sf::Vector2f pivotPos = testPiece.blocks[0].getBlockPosition();
	std::vector<sf::Vector2f> newPoints;
	bool isObstructed = false;

	for (int i = 0; i < testPiece.blocks.size(); i++)
	{
		sf::Vector2f oldPos = testPiece.blocks[i].getBlockPosition();

		float newX = -(oldPos.y - pivotPos.y) + pivotPos.x;
		float newY = oldPos.x - pivotPos.x + pivotPos.y;


		if (newX < 0 || newX >= gameAreaDimensions.x || newY < 0 || newY >= gameAreaDimensions.y || gameArea.grid[newY][newX].occupied)
		{
			isObstructed = true;
		}

		newPoints.push_back(sf::Vector2f(newX, newY));

		/*# rotates the shape clockwise
			def rotateCW(self) :
			newBlockX = [0, 0, 0, 0]
			newBlockY = [0, 0, 0, 0]
			#rotate all of the blocks
			for i in range(self.numblocks) :
				newBlockX[i] = -(self.blockList[i].gridYpos - self.blockList[0].gridYpos) +
				self.blockList[0].gridXpos
				newBlockY[i] = (self.blockList[i].gridXpos - self.blockList[0].gridXpos) +
				self.blockList[0].gridYpos
				self.blockList[i].gridXpos = newBlockX[i]
				self.blockList[i].gridYpos = newBlockY[i]*/
	}

	if (!isObstructed)
	{
		for (int i = 0; i < newPoints.size(); i++)
		{
			testPiece.blocks[i].setBlockPosition(newPoints[i]);
		}
	}
}
