#pragma once
#include <SFML/Graphics.hpp>

extern int blockSize;
extern sf::Color gameBorderColor;
extern sf::Color gameBackgroundColor;

class Cell
{
public:
	int gridPosX, gridPosY;
	Cell(int gridPosX, int gridPosY);
	sf::RectangleShape cellVisual;
	void draw(sf::RenderWindow& window);
	bool isOccupied;
	~Cell();
};