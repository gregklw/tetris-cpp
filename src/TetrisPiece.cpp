#include "../header/TetrisPiece.h"

TetrisPiece::TetrisPiece(std::array<TetrisBlock, 4>& blocks) : blocks(blocks)
{
	this->blocks = blocks;
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
