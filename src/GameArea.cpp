#include "../header/GameArea.h"

GameArea::GameArea()
{
	gameAreaVisual.setOutlineThickness(-5);
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
			if (currentPosX == 0 || grid[currentPosY][currentPosX - 1].isOccupied)
			{
				return true;
			}
		}
		//-------check if piece is touching right wall moving right
		else if (velocity.x > 0)
		{
			if (currentPosX == gameAreaDimensions.x - 1 || grid[currentPosY][currentPosX + 1].isOccupied)
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
			if (currentPosX == grid[currentPosY][x].gridPosX && grid[currentPosY + 1][x].isOccupied)
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
		grid[position.y][position.x].isOccupied = true;
		grid[position.y][position.x].cellVisual.setFillColor(piece.blocks[i].blockShape.getFillColor());
	}
	piece = getNewPiece();
}

TetrisPiece GameArea::getNewPiece()
{
	return TetrisPiece(sf::Color::Green);
}


GameArea::~GameArea()
{
}

