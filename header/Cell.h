#pragma once
#include <SFML/Graphics.hpp>

extern int blockSize;
extern sf::Color emptyBorderColor;
extern sf::Color occupiedBorderColor;
extern sf::Color gameBackgroundColor;

class Cell
{
public:
	int gridPosX, gridPosY;
	Cell(int gridPosX, int gridPosY);
	sf::RectangleShape cellVisual;
	void draw(sf::RenderWindow& window);
	void occupyCell(sf::Color color);
	void copyCell(Cell cell);
	void clearCell();
	bool occupied;
	~Cell();
};