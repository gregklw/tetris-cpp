#pragma once
#include <SFML/Graphics.hpp>
#include "../header/Cell.h"
#include "../header/TetrisPiece.h"
#include "../header/TetrisEvents.h"

extern int currentScore;
extern const int autoMoveDownCooldown;
extern const int gameAreaBlockSize;
extern const int previewPieceSize;
extern const sf::Color emptyBorderColor;
extern const sf::Color gameAreaBackgroundColor;
extern const sf::Color ghostFillColor;
extern const sf::Vector2f gameAreaDimensions;
extern const sf::Vector2f gameAreaPosition;
extern const sf::Vector2f pieceSpawnPosition;
extern const sf::Vector2f pieceGridSpawnPosition;
extern const std::vector<TetrisPiece> tetraminoList;
extern std::vector<TetrisPiece> nextPieces;
extern TetrisEvents tetrisEvents;

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

	void movePieceDownToLowestPoint(TetrisPiece& piece, std::vector<sf::Vector2f>& gridPoints);
	void rotatePiece();
	void movePieceLeft();
	void movePieceRight();
	void holdPiece();
	void moveCurrentPieceDown();
	void hardDropCurrentPiece();
	void addToScore();

	void printGridPositions();

	void spawnTetraminoOnGameArea(TetrisPiece piece);
	TetrisPiece grabTopPreviewPiece();

	std::vector<std::vector<Cell>> grid;
	~GameArea();

private:
	void movePieceDown(TetrisPiece& piece, std::vector<sf::Vector2f>& gridPositions);
	void setGridPoints(std::vector<sf::Vector2f>& gridPoints, std::vector<sf::Vector2f> newGridPoints);
	void moveGridPoints(std::vector<sf::Vector2f>& gridPoints, sf::Vector2f amount);
	void autoMoveCurrentPieceDown();
	bool isToppedOut(std::vector<TetrisBlock> pieceBlocks);
	void resetGame();

	sf::RectangleShape gameAreaVisual;
	TetrisPiece currentPiece;
	std::vector<sf::Vector2f> currentGridPositions;
	TetrisPiece ghostPiece;
	std::vector<sf::Vector2f> ghostGridPositions;
	int autoMoveDownTimer;
};