#include "../header/TetrisBlock.h"

TetrisBlock::TetrisBlock(sf::Vector2f gridPosition, sf::Color color)
{
	this->gridPosition = gridPosition;
	blockShape.setOutlineThickness(-blockSize / 10.0f);
	blockShape.setOutlineColor(blockBorderColor);
	
	blockShape.setFillColor(color);
	blockShape.setSize(sf::Vector2f(blockSize, blockSize));
	blockPosition = gameAreaStartPosition + sf::Vector2f(gridPosition.x * blockSize, gridPosition.y * blockSize);
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
	blockPosition += sf::Vector2f(position.x * blockSize, position.y * blockSize);
}

void TetrisBlock::setScreenPosition(sf::Vector2f position)
{
	blockPosition = sf::Vector2f(position.x * blockSize, position.y * blockSize);
}

void TetrisBlock::moveBlockByGridPosition(sf::Vector2f position)
{
	gridPosition += position;
	blockPosition += sf::Vector2f(position.x * blockSize, position.y * blockSize);
}

void TetrisBlock::setGridPosition(sf::Vector2f position)
{
	gridPosition = position;
	blockPosition = gameAreaStartPosition + sf::Vector2f(position.x * blockSize, position.y * blockSize);
}

sf::Vector2f TetrisBlock::getGridPosition()
{
	return gridPosition;
}
