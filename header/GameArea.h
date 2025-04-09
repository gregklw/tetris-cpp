#pragma once
#include <SFML/Graphics.hpp>
#include "../header/Cell.h"
#include "../header/TetrisPiece.h"
#include <queue>

extern int gameAreaBlockSize;
extern int previewPieceSize;
extern sf::Color emptyBorderColor;
extern sf::Color gameAreaBackgroundColor;
extern sf::Vector2f gameAreaDimensions;
extern sf::Vector2f gameAreaPosition;
extern sf::Vector2f pieceSpawnPosition;
extern sf::Vector2f pieceGridSpawnPosition;
extern std::vector<TetrisPiece> tetraminoList;

extern bool holdPieceOnPress;
extern bool hardDroppedOnPress;
extern bool rotateOnPress;
extern sf::Vector2f holdBoxLocation;
extern TetrisPiece heldPiece;
extern TetrisPiece* heldPiecePointer;
extern TetrisPiece getNewTetramino(sf::Vector2f screenStartPosition, int size);

class GameArea
{
public:
	GameArea(sf::Vector2f startPosition);

	void update(sf::RenderWindow& window);

	void previewHardDrop(sf::RenderWindow& window);
	bool checkHorizontalCollision(std::vector<sf::Vector2f> gridPoints, sf::Vector2f velocity);
	bool checkVerticalCollision(std::vector<sf::Vector2f> gridPoints);
	void occupyCells(TetrisPiece piece);
	void checkAndClearRow(int lowestRowToStart);
	void clearRow(int row);
	void updateGameAfterVerticalCollision(TetrisPiece piece);
	void moveRowsDownAfterClearing(int clearedRow);

	void hardDropCurrentPiece();
	void movePieceDownToLowestPoint(TetrisPiece& piece, std::vector<sf::Vector2f>& gridPoints);
	void rotatePiece();
	void checkPieceLanding();
	void movePieceLeft();
	void movePieceRight();
	void holdPiece();
	void moveCurrentPieceDown();

	void printGridPositions();

	void spawnTetraminoOnGameArea(TetrisPiece piece);
	TetrisPiece grabTopPreviewPiece();

	std::vector<std::vector<Cell>> grid;
	std::vector<TetrisPiece> nextPieces;
	~GameArea();

private:
	void movePieceDown(TetrisPiece& piece, std::vector<sf::Vector2f>& gridPositions);
	void setGridPoints(std::vector<sf::Vector2f>& gridPoints, std::vector<sf::Vector2f> newGridPoints);
	void moveGridPoints(std::vector<sf::Vector2f>& gridPoints, sf::Vector2f amount);

	sf::RectangleShape gameAreaVisual;
	TetrisPiece currentPiece;
	std::vector<sf::Vector2f> currentGridPositions;
	TetrisPiece ghostPiece;
	std::vector<sf::Vector2f> ghostGridPositions;

};