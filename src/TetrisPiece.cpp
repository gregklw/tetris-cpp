#include "../header/TetrisPiece.h"

TetrisPiece::TetrisPiece(sf::Color color)
{
	std::vector<TetrisBlock> blocks
	{
		TetrisBlock(sf::Vector2f(0, 0),  color),
		TetrisBlock(sf::Vector2f(0, 1), color),
		TetrisBlock(sf::Vector2f(0, 2), color),
		TetrisBlock(sf::Vector2f(0, 3), color)
	};

	this->blocks = blocks;
}

void TetrisPiece::moveLeft()
{
	movePiece(sf::Vector2f(-1, 0));
}

void TetrisPiece::moveRight()
{
	movePiece(sf::Vector2f(1, 0));
}

void TetrisPiece::moveDown()
{
	movePiece(sf::Vector2f(0, 1));
}

void TetrisPiece::movePiece(sf::Vector2f amountToMove)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].moveBlock(amountToMove);
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
