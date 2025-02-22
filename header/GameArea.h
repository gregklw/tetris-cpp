#pragma once
#include <SFML/Graphics.hpp>
#include "../header/Cell.h"
#include "../header/TetrisPiece.h"

extern int blockSize;
extern sf::Color gameBorderColor;
extern sf::Color gameBackgroundColor;
extern sf::Vector2f gameAreaDimensions;

class GameArea
{
public:
	GameArea();

	void update(sf::RenderWindow& window);
	bool checkHorizontalCollision(TetrisPiece piece, sf::Vector2f velocity);
	bool checkVerticalCollision(TetrisPiece piece);
	void occupyCells(TetrisPiece& piece);
	std::vector<std::vector<Cell>> grid;
	TetrisPiece getNewPiece();

	~GameArea();

private:
	sf::RectangleShape gameAreaVisual;

};