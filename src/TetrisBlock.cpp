#include "../header/TetrisBlock.h"

TetrisBlock::TetrisBlock(sf::Vector2f startPosition, sf::Color color)
{
	blockShape.setOutlineThickness(-5.0f);
	blockShape.setOutlineColor(sf::Color::White);
	
	blockShape.setFillColor(color);
	position = startPosition;
	setSize(sf::Vector2f(blockSize, blockSize));
}

TetrisBlock::~TetrisBlock()
{
}

void TetrisBlock::update(sf::RenderWindow& window)
{
	blockShape.setPosition(position);
	blockShape.setSize(size);
	window.draw(blockShape);
}

void TetrisBlock::moveBlock(sf::Vector2f position)
{
	this->position += position;
}

void TetrisBlock::setSize(sf::Vector2f size)
{
	this->size = size;
}


