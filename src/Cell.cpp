#include "../header/Cell.h"

Cell::Cell(int gridPosX, int gridPosY)
{
	this->gridPosX = gridPosX;
	this->gridPosY = gridPosY;
	occupied = false;
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

void Cell::occupyCell(sf::Color color)
{
	occupied = true;
	cellVisual.setFillColor(color);
}

void Cell::copyCell(Cell cell)
{
	cellVisual.setFillColor(cell.cellVisual.getFillColor());
	occupied = cell.occupied;
}

void Cell::clearCell()
{
	occupied = false;
	cellVisual.setFillColor(gameBackgroundColor);
}

Cell::~Cell()
{
}
