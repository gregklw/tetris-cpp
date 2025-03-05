#include "../header/GameController.h"

GameController::GameController()
{
	hardDroppedOnPress = false;
	rotateOnPress = false;
}

void GameController::checkLandedOnPieceBelow(TetrisPiece& piece, GameArea& gameArea)
{
	if (!gameArea.checkVerticalCollision(piece))
	{
		movePieceDown(piece, gameArea);
	}
	else
	{
		gameArea.occupyCells(piece);
		int lowestRowToStart = 0;

		for (int i = 0; i < piece.blocks.size(); i++)
		{
			int yPos = piece.blocks[i].getGridPosition().y;
			if (lowestRowToStart < yPos)
			{
				lowestRowToStart = yPos;
			}
		}

		std::cout << lowestRowToStart << " Lowest Row \n";

		gameArea.checkAndClearRow(lowestRowToStart);
		piece = gameArea.getNewPiece();
	}
}

void GameController::movePieceLeft(TetrisPiece& piece, GameArea& gameArea)
{
	sf::Vector2f left = sf::Vector2f(-1, 0);
	if (!gameArea.checkHorizontalCollision(piece, left))
	{
		piece.movePiece(left);
	}
}

void GameController::movePieceRight(TetrisPiece& piece, GameArea& gameArea)
{
	sf::Vector2f right = sf::Vector2f(1, 0);
	if (!gameArea.checkHorizontalCollision(piece, right))
	{
		piece.movePiece(right);
	}
}

void GameController::movePieceDown(TetrisPiece& piece, GameArea& gameArea)
{
	sf::Vector2f down = sf::Vector2f(0, 1);
	if (!gameArea.checkVerticalCollision(piece))
	{
		piece.movePiece(down);
	}
	else
	{
		//update game area
		gameArea.updateGameAfterLineClear(piece);
	}
}

void GameController::hardDropPiece(TetrisPiece& piece, GameArea& gameArea)
{
	if (hardDroppedOnPress) return;

	while (!gameArea.checkVerticalCollision(piece))
	{
		movePieceDown(piece, gameArea);
	}
	gameArea.updateGameAfterLineClear(piece);
}

void GameController::rotatePiece(TetrisPiece& piece, GameArea& gameArea)
{
	if (rotateOnPress) return;

	std::vector<TetrisBlock>& targetBlocks = piece.blocks;

	for (int i = 0; i < targetBlocks.size(); i++)
	{
		sf::Vector2f pivotPos(targetBlocks[i].getGridPosition().x, targetBlocks[i].getGridPosition().y);
		std::vector<sf::Vector2f> newPoints;
		bool isObstructed = false;

		for (int j = 0; j < targetBlocks.size(); j++)
		{
			sf::Vector2f oldPos(targetBlocks[j].getGridPosition().x, targetBlocks[j].getGridPosition().y);

			float newX = -(oldPos.y - pivotPos.y) + pivotPos.x;
			float newY = oldPos.x - pivotPos.x + pivotPos.y;


			if (newX < 0 || newX >=  gameAreaDimensions.x || newY < 0 || newY >= gameAreaDimensions.y || gameArea.grid[newY][newX].occupied)
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

		//if not obstructed then apply the new rotation points and end this function
		if (!isObstructed)
		{
			for (int j = 0; j < newPoints.size(); j++)
			{
				targetBlocks[j].setPosition(sf::Vector2f(newPoints[j].x, newPoints[j].y));
			}
			break;
		}
		//otherwise if its obstructed and if counter isn't exceeding the block size then try the next block as a pivot point
	}
}

GameController::~GameController()
{
}
