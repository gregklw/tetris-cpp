#include "../header/Cell.h"

Cell::Cell(int gridPosX, int gridPosY)
{
	this->gridPosX = gridPosX;
	this->gridPosY = gridPosY;
	isOccupied = false;
	cellVisual.setSize(sf::Vector2f(blockSize, blockSize));
	cellVisual.setPosition(sf::Vector2f(gridPosX * blockSize, gridPosY * blockSize));
	cellVisual.setOutlineColor(gameBorderColor);
	cellVisual.setOutlineThickness(-1);
	cellVisual.setFillColor(gameBackgroundColor);
}

void Cell::draw(sf::RenderWindow& window)
{
	window.draw(cellVisual);
}

Cell::~Cell()
{
}
