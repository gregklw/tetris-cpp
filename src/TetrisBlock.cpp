#include "../header/TetrisBlock.h"

TetrisBlock::TetrisBlock(sf::Vector2f startGridPosition, sf::Vector2f startScreenPosition, sf::Color color, int size)
{
	//this->gridPosition = gridPosition;
	//blockStartGridPos = gridPosition;
	blockStartGridPos = startGridPosition;
	blockShape.setOutlineThickness(-size / 10.0f);
	blockShape.setOutlineColor(blockBorderColor);

	blockShape.setFillColor(color);
	blockShape.setSize(sf::Vector2f(size, size));
	//blockShape.setPosition(sf::Vector2f(gridPosition.x * size, gridPosition.y * size));
	blockShape.setPosition(sf::Vector2f(startScreenPosition) + sf::Vector2f(startGridPosition.x * size, startGridPosition.y * size));
}

TetrisBlock::~TetrisBlock()
{
}

void TetrisBlock::update(sf::RenderWindow& window)
{
	window.draw(blockShape);
}

//void TetrisBlock::moveBlockByGrid(sf::Vector2f gridPosition)
//{
//	blockShape.move(sf::Vector2f(gridPosition.x * blockSize, gridPosition.y * blockSize));
//	this->gridPosition += gridPosition;
//}

void TetrisBlock::moveBlock(sf::Vector2f amount)
{
	blockShape.move(sf::Vector2f(amount.x, amount.y));
}

void TetrisBlock::setPosition(sf::Vector2f position)
{
	blockShape.setPosition(position);
}

//void TetrisBlock::setGridPosition(sf::Vector2f position)
//{
//	gridPosition = position;
//}

void TetrisBlock::setBlockSize(int newBlockSize)
{
	blockShape.setSize(sf::Vector2f(newBlockSize, newBlockSize));;
}

void TetrisBlock::printBlock()
{
	/*std::cout << "Grid position: " << gridPosition.x << "/" << gridPosition.y << "\n";
	std::cout << "Screen position: " << blockShape.getPosition().x << "/" << blockShape.getPosition().y << "\n";*/
}

//sf::Vector2f TetrisBlock::getGridPosition()
//{
//	return gridPosition;
//}

sf::Vector2f TetrisBlock::getBlockStartGridPos()
{
	return blockStartGridPos;
}
