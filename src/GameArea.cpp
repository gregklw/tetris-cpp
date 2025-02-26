#include "../header/GameArea.h"

GameArea::GameArea()
{
	gameAreaVisual.setOutlineThickness(-blockSize / 10.0f);
	gameAreaVisual.setOutlineColor(gameBorderColor);
	gameAreaVisual.setFillColor(gameBackgroundColor);
	gameAreaVisual.setSize(sf::Vector2f(gameAreaDimensions.x * blockSize, gameAreaDimensions.y * blockSize));

	for (int y = 0; y < gameAreaDimensions.y; y++)
	{
		std::vector<Cell> cell;
		grid.push_back(cell);
		for (int x = 0; x < gameAreaDimensions.x; x++)
		{
			grid[y].push_back(Cell(x, y));
		}
	}
}

void GameArea::update(sf::RenderWindow& window)
{
	window.draw(gameAreaVisual);
	for (int y = 0; y < gameAreaDimensions.y; y++)
	{
		for (int x = 0; x < gameAreaDimensions.x; x++)
		{
			grid[y][x].draw(window);
		}
	}
}

bool GameArea::checkHorizontalCollision(TetrisPiece piece, sf::Vector2f velocity)
{
	for (int i = 0; i < piece.blocks.size(); i++)
	{
		int currentPosX = piece.blocks[i].getBlockPosition().x;
		int currentPosY = piece.blocks[i].getBlockPosition().y;

		//-------check if piece is touching left wall moving left
		if (velocity.x < 0)
		{
			if (currentPosX == 0 || grid[currentPosY][currentPosX - 1].occupied)
			{
				return true;
			}
		}
		//-------check if piece is touching right wall moving right
		else if (velocity.x > 0)
		{
			if (currentPosX == gameAreaDimensions.x - 1 || grid[currentPosY][currentPosX + 1].occupied)
			{
				return true;
			}
		}
	}

	return false;
}

bool GameArea::checkVerticalCollision(TetrisPiece piece)
{
	for (int i = 0; i < piece.blocks.size(); i++)
	{
		int currentPosX = piece.blocks[i].getBlockPosition().x;
		int currentPosY = piece.blocks[i].getBlockPosition().y;

		//-------check if piece is touching bottom
		if (currentPosY == gameAreaDimensions.y - 1)
		{
			return true;
		}

		//-------check if piece is touching occupied area below it
		for (int x = 0; x < grid[currentPosY].size(); x++)
		{
			if (currentPosX == grid[currentPosY][x].gridPosX && grid[currentPosY + 1][x].occupied)
			{
				/*occupyCells(piece);
				return;*/
				return true;
			}
		}
	}
	return false;
}

void GameArea::occupyCells(TetrisPiece& piece)
{
	for (int i = 0; i < piece.blocks.size(); i++)
	{
		sf::Vector2f position = piece.blocks[i].getBlockPosition();
		grid[position.y][position.x].occupyCell(piece.blocks[i].blockShape.getFillColor());
	}
}

void GameArea::checkAndClearRow(int lowestRowToStart)
{
	if (lowestRowToStart < 0) return;

	bool assertCompleteRow = true;
	//loop to check if any one of the cells are not occupied
	for (int j = 0; j < grid[lowestRowToStart].size(); j++)
	{
		std::cout << lowestRowToStart << " lowest row \n";
		std::cout << grid[lowestRowToStart][j].gridPosX << " xPos \n";
		std::cout << grid[lowestRowToStart][j].gridPosY << " yPos \n";
		std::cout << grid[lowestRowToStart][j].occupied << " is occupied \n";
		std::cout << "-------------------------------------------------\n";


		if (!grid[lowestRowToStart][j].occupied)
		{
			
			assertCompleteRow = false;
			break;
		}
	}
	//if row is complete then clear it and move all the other stuff above it down
	if (assertCompleteRow)
	{
		std::cout << lowestRowToStart << " the current row\n";
		clearRow(lowestRowToStart);
		moveRowsDownAfterClearing(lowestRowToStart);
	}
	else
	{
		lowestRowToStart--;
	}

	checkAndClearRow(lowestRowToStart);
}

void GameArea::clearRow(int row)
{
	for (int i = 0; i < grid[row].size(); i++)
	{
		grid[row][i].clearCell();
	}
}

void GameArea::moveRowsDownAfterClearing(int clearedRow)
{
	std::cout << clearedRow << "number\n";
	while (clearedRow >= 1)
	{
		std::cout << clearedRow << " CLEARED\n";
		//go through each member and move it down to target row

		for (int i = 0; i < grid[clearedRow].size(); i++)
		{
			std::cout << clearedRow << " ROWS BEING MOVED\n";
			/*Cell cellToCopy(grid[clearedRow - 1][i]);
			grid[clearedRow][i].cellVisual = grid[clearedRow - 1][i].cellVisual;*/
			grid[clearedRow][i].copyCell(grid[clearedRow - 1][i]);
		}
		clearedRow--;
	}
}

TetrisPiece GameArea::getNewPiece()
{
	return tetraminoList[std::rand() % tetraminoList.size()];
}


GameArea::~GameArea()
{
}

