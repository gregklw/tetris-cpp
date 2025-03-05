#include "../header/Cell.h"

Cell::Cell(int gridPosX, int gridPosY, sf::Vector2f screenPosition)
{
	this->screenPosition = screenPosition;
	this->gridPosX = gridPosX;
	this->gridPosY = gridPosY;
	occupied = false;
	cellVisual.setSize(sf::Vector2f(blockSize, blockSize));
	cellVisual.setPosition(sf::Vector2f(screenPosition.x + gridPosX * blockSize, screenPosition.y + gridPosY * blockSize));
	cellVisual.setOutlineColor(gameBackgroundColor);
	cellVisual.setOutlineThickness(-1);
	cellVisual.setFillColor(gameBackgroundColor);
}

void Cell::draw(sf::RenderWindow& window)
{
	window.draw(cellVisual);
}

void Cell::occupyCell(sf::Color color)
{
	occupied = true;
	cellVisual.setOutlineColor(occupiedBorderColor);
	cellVisual.setFillColor(color);
}

void Cell::copyCell(Cell cell)
{
	cellVisual.setFillColor(cell.cellVisual.getFillColor());
	occupied = cell.occupied;
	if (occupied) cellVisual.setOutlineColor(occupiedBorderColor);
}

void Cell::clearCell()
{
	occupied = false;
	cellVisual.setOutlineColor(emptyBorderColor);
	cellVisual.setFillColor(gameBackgroundColor);
}

Cell::~Cell()
{
}
