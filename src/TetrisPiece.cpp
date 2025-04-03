#include "../header/TetrisPiece.h"

TetrisPiece::TetrisPiece()
{
}

TetrisPiece::TetrisPiece(std::array<sf::Vector2f, 4> blockPivots, sf::Vector2f screenStartPosition, sf::Color color, int blockSize)
{
	std::vector<TetrisBlock> blocks;

	for (int i = 0; i < blockPivots.size(); i++)
	{
		blocks.push_back(TetrisBlock(blockPivots[i], screenStartPosition, color, blockSize));
	}

	/*for (int i = 0; i < blocks.size(); i++)
	{
		sf::Vector2f blockPivot = blockPivots[i];
		blocks[i].blockShape.setPosition(screenStartPosition + sf::Vector2f(blockPivot.x * blockSize, blockPivot.y * blockSize));
	}*/

	this->blocks = blocks;
}

void TetrisPiece::setPosition(sf::Vector2f position)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		TetrisBlock& block = blocks[i];
		block.setPosition(position + sf::Vector2f(block.getBlockStartGridPos().x * blockSize, block.getBlockStartGridPos().y * blockSize));
	}
}

//void TetrisPiece::setGridPosition(sf::Vector2f targetPosition)
//{
//	int highestGridPosY = 0;
//
//	for (int i = 0; i < blocks.size(); i++)
//	{
//		if (highestGridPosY < blocks[i].getGridPosition().y)
//		{
//			highestGridPosY = blocks[i].getGridPosition().y;
//		}
//	}
//
//	sf::Vector2f position = (sf::Vector2f(0, highestGridPosY) + targetPosition) - blocks[0].getGridPosition();
//	for (int i = 0; i < blocks.size(); i++)
//	{
//		blocks[i].setGridPosition(position + blocks[i].getBlockStartGridPos());
//	}
//}
//
//void TetrisPiece::movePieceByGrid(sf::Vector2f gridPosition)
//{
//	for (int i = 0; i < blocks.size(); i++)
//	{
//		blocks[i].moveBlockByGrid(gridPosition);
//	}
//}

void TetrisPiece::movePiece(sf::Vector2f amount)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].moveBlock(amount);
	}
}

void TetrisPiece::setSize(sf::Vector2f size)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].blockShape.setSize(size);
	}
}

void TetrisPiece::update(sf::RenderWindow& window)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].update(window);
	}
}

void TetrisPiece::printPiece()
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].printBlock();
	}
}

TetrisPiece::~TetrisPiece()
{
}
