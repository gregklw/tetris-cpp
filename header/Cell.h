#pragma once
#include <SFML/Graphics.hpp>

extern int blockSize;
extern sf::Color emptyBorderColor;
extern sf::Color occupiedBorderColor;
extern sf::Color gameAreaBackgroundColor;

class Cell
{
public:
	int gridPosX, gridPosY;
	sf::Vector2f screenPosition;
	Cell(int gridPosX, int gridPosY, sf::Vector2f screenPosition);
	sf::RectangleShape cellVisual;
	void draw(sf::RenderWindow& window);
	void occupyCell(sf::Color color);
	void copyCell(Cell cell);
	void clearCell();
	bool occupied;
	~Cell();
};