#include "../header/TetrisPiece.h"

TetrisPiece::TetrisPiece(std::array<sf::Vector2f, 4> blockIndices, sf::Color color)
{
	std::vector<TetrisBlock> blocks;

	for (int i = 0; i < blockIndices.size(); i++)
	{
		blocks.push_back(TetrisBlock(blockIndices[i], color));
	}

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
