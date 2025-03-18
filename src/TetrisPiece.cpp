#include "../header/TetrisPiece.h"

TetrisPiece::TetrisPiece()
{
}

TetrisPiece::TetrisPiece(std::array<sf::Vector2f, 4> blockIndices, sf::Color color, int blockSize)
{
	std::vector<TetrisBlock> blocks;

	for (int i = 0; i < blockIndices.size(); i++)
	{
		blocks.push_back(TetrisBlock(blockIndices[i], color));
	}
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].setBlockSize(blockSize);
	}

	this->blocks = blocks;
}

void TetrisPiece::setScreenPosition(sf::Vector2f position)
{
	sf::Vector2f amountToMove = position - blocks[0].getGridPosition();
	for (int i = 0; i < blocks.size(); i++)
	{
		std::cout << amountToMove.x << "/" << amountToMove.y << "\n";
		blocks[i].moveBlockByScreenPosition(amountToMove);
	}
}

void TetrisPiece::setGridPosition(sf::Vector2f position)
{
	sf::Vector2f amountToMove = position - blocks[0].getGridPosition();
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].moveBlockByGridPosition(amountToMove);
	}
}

void TetrisPiece::setSize(sf::Vector2f size)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].blockShape.setSize(size);
	}
}

void TetrisPiece::movePieceByGridPosition(sf::Vector2f amountToMove)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].moveBlockByGridPosition(amountToMove);
	}
}

void TetrisPiece::update(sf::RenderWindow& window)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].update(window);
	}
}

TetrisPiece::~TetrisPiece()
{
}
