#include "../header/GameArea.h"

GameArea::GameArea(sf::Vector2f startPosition)
{
	gameAreaVisual.setPosition(startPosition);
	gameAreaVisual.setOutlineThickness(-blockSize / 10.0f);
	gameAreaVisual.setOutlineColor(emptyBorderColor);
	gameAreaVisual.setFillColor(gameBackgroundColor);
	gameAreaVisual.setSize(sf::Vector2f(gameAreaDimensions.x * blockSize, gameAreaDimensions.y * blockSize));

	for (int y = 0; y < gameAreaDimensions.y; y++)
	{
		std::vector<Cell> cellRow;
		grid.push_back(cellRow);
		for (int x = 0; x < gameAreaDimensions.x; x++)
		{
			grid[y].push_back(Cell(x, y, startPosition));
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

void GameArea::previewHardDrop(sf::RenderWindow& window, TetrisPiece piece)
{
	TetrisPiece preview(piece);

	for (int i = 0; i < preview.blocks.size(); i++)
	{
		preview.blocks[i].blockShape.setFillColor(gameBackgroundColor);
	}

	sf::Vector2f down = sf::Vector2f(0, 1);
	while (!checkVerticalCollision(preview))
	{
		preview.movePiece(down);
	}
	preview.update(window);
}

bool GameArea::checkHorizontalCollision(TetrisPiece piece, sf::Vector2f velocity)
{
	for (int i = 0; i < piece.blocks.size(); i++)
	{
		int gridPosX = piece.blocks[i].getGridPosition().x;
		int gridPosY = piece.blocks[i].getGridPosition().y;

		//-------check if piece is touching left wall moving left
		if (velocity.x < 0)
		{
			if (gridPosX == 0 || grid[gridPosY][gridPosX - 1].occupied)
			{
				return true;
			}
		}
		//-------check if piece is touching right wall moving right
		else if (velocity.x > 0)
		{
			if (gridPosX == gameAreaDimensions.x - 1 || grid[gridPosY][gridPosX + 1].occupied)
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
		int gridPosX = piece.blocks[i].getGridPosition().x;
		int gridPosY = piece.blocks[i].getGridPosition().y;

		//std::cout << gridPosY << " / " << piece.blocks[i].getBlockPosition().y << "\n";

		//-------check if piece is touching bottom
		if (gridPosY == gameAreaDimensions.y - 1)
		{
			return true;
		}

		//-------check if piece is touching occupied area below it
		for (int x = 0; x < grid[gridPosY].size(); x++)
		{
			if (gridPosX == grid[gridPosY][x].gridPosX && grid[gridPosY + 1][x].occupied)
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
		grid[piece.blocks[i].getGridPosition().y][piece.blocks[i].getGridPosition().x].occupyCell(piece.blocks[i].blockShape.getFillColor());
	}
}

void GameArea::checkAndClearRow(int lowestRowToStart)
{
	if (lowestRowToStart < 0) return;

	bool assertCompleteRow = true;
	//loop to check if any one of the cells are not occupied
	for (int j = 0; j < grid[lowestRowToStart].size(); j++)
	{
		if (!grid[lowestRowToStart][j].occupied)
		{
			
			assertCompleteRow = false;
			break;
		}
	}
	//if row is complete then clear it and move all the other stuff above it down
	if (assertCompleteRow)
	{
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

void GameArea::updateGameAfterLineClear(TetrisPiece& piece)
{
	occupyCells(piece);
	int lowestRowToStart = 0;

	for (int i = 0; i < piece.blocks.size(); i++)
	{
		int gridPosY = piece.blocks[i].getGridPosition().y;
		if (lowestRowToStart < gridPosY)
		{
			lowestRowToStart = gridPosY;
		}
	}
	checkAndClearRow(lowestRowToStart);
	piece = getNewPiece();
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
			grid[clearedRow][i].copyCell(grid[clearedRow - 1][i]);
			grid[clearedRow - 1][i].clearCell();
		}
		clearedRow--;
	}
}

TetrisPiece GameArea::getNewPiece()
{
	TetrisPiece newPiece = tetraminoList[std::rand() % tetraminoList.size()];
	std::vector newBlocks = newPiece.blocks;
	//for (int i = 0; i < newBlocks.size(); i++)
	//{
	//	newBlocks[i].moveBlock(gameAreaStartPosition);
	//	//std::cout << newBlocks[i].getBlockPosition().x << ", " << newBlocks[i].getBlockPosition().y << "\n";
	//}
	newPiece.blocks = newBlocks;
	return newPiece;
}


GameArea::~GameArea()
{
}

