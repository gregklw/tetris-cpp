#include "../header/TetrisBlock.h"

TetrisBlock::TetrisBlock(sf::Vector2f startPosition, sf::Color color)
{
	blockShape.setOutlineThickness(-blockSize / 10.0f);
	blockShape.setOutlineColor(sf::Color::White);
	
	blockShape.setFillColor(color);
	blockShape.setSize(sf::Vector2f(blockSize, blockSize));
	blockPosition = startPosition;
}

TetrisBlock::~TetrisBlock()
{
}

void TetrisBlock::update(sf::RenderWindow& window)
{
	blockShape.setPosition(sf::Vector2f(blockPosition.x * blockSize, blockPosition.y * blockSize));
	window.draw(blockShape);
}

void TetrisBlock::moveBlock(sf::Vector2f position)
{
	blockPosition += sf::Vector2f(position);
}

void TetrisBlock::setBlockPosition(sf::Vector2f& blockPosition)
{
	this->blockPosition = blockPosition;
}

sf::Vector2f TetrisBlock::getBlockPosition()
{
	return blockPosition;
}


