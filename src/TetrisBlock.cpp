#include "../header/TetrisBlock.h"

TetrisBlock::TetrisBlock(sf::Vector2f gridPosition, sf::Color color)
{
	this->gridPosition = gridPosition;
	blockShape.setOutlineThickness(-currentBlockSize / 10.0f);
	blockShape.setOutlineColor(blockBorderColor);
	
	blockShape.setFillColor(color);
	blockShape.setSize(sf::Vector2f(currentBlockSize, currentBlockSize));
	blockPosition = sf::Vector2f(gridPosition.x * currentBlockSize, gridPosition.y * currentBlockSize);
}

TetrisBlock::~TetrisBlock()
{
}

void TetrisBlock::update(sf::RenderWindow& window)
{
	blockShape.setPosition(sf::Vector2f(blockPosition.x, blockPosition.y));
	window.draw(blockShape);
}

void TetrisBlock::moveBlockByScreenPosition(sf::Vector2f position)
{
	blockPosition += sf::Vector2f(position.x, position.y);
}

void TetrisBlock::setScreenPosition(sf::Vector2f position)
{
	blockPosition = sf::Vector2f(position.x * currentBlockSize, position.y * currentBlockSize);
}

void TetrisBlock::moveBlockByGridPosition(sf::Vector2f position)
{
	gridPosition += position;
	blockPosition += sf::Vector2f(position.x * currentBlockSize, position.y * currentBlockSize);
}

void TetrisBlock::setGridPosition(sf::Vector2f position)
{
	gridPosition = position;
	blockPosition = gameAreaStartPosition + sf::Vector2f(position.x * currentBlockSize, position.y * currentBlockSize);
}

void TetrisBlock::setBlockSize(int newBlockSize)
{
	currentBlockSize = newBlockSize;
}

sf::Vector2f TetrisBlock::getGridPosition()
{
	return gridPosition;
}
