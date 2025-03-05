#pragma once
#include <SFML/Graphics.hpp>
#include "../header/Cell.h"
#include "../header/TetrisPiece.h"
#include <unordered_set>

extern int blockSize;
extern sf::Color emptyBorderColor;
extern sf::Color gameBackgroundColor;
extern sf::Vector2f gameAreaDimensions;
extern sf::Vector2f gameAreaStartPosition;
extern std::vector<TetrisPiece> tetraminoList;

class GameArea
{
public:
	GameArea(sf::Vector2f startPosition);

	void update(sf::RenderWindow& window);
	void previewHardDrop(sf::RenderWindow& window, TetrisPiece piece);
	bool checkHorizontalCollision(TetrisPiece piece, sf::Vector2f velocity);
	bool checkVerticalCollision(TetrisPiece piece);
	void occupyCells(TetrisPiece& piece);
	void checkAndClearRow(int lowestRowToStart);
	void clearRow(int row);
	void updateGameAfterLineClear(TetrisPiece& piece);
	void moveRowsDownAfterClearing(int clearedRow);
	std::vector<std::vector<Cell>> grid;
	TetrisPiece getNewPiece();

	~GameArea();

private:
	sf::RectangleShape gameAreaVisual;
};