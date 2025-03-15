#pragma once
#include <SFML/Window.hpp>
#include "TetrisPiece.h"
#include "GameArea.h"

extern bool holdPieceOnPress;
extern bool hardDroppedOnPress;
extern bool rotateOnPress;
extern sf::Vector2f holdBoxLocation;
extern TetrisPiece heldPiece;
extern TetrisPiece* heldPiecePointer;

class GameController
{
public:
	GameController();
	void hardDropPiece(TetrisPiece& piece, GameArea& gameArea);
	void rotatePiece(TetrisPiece& piece, GameArea& gameArea);
	void checkLandedOnPieceBelow(TetrisPiece& piece, GameArea& gameArea);
	void movePieceLeft(TetrisPiece& piece, GameArea& gameArea);
	void movePieceRight(TetrisPiece& piece, GameArea& gameArea);
	void movePieceDown(TetrisPiece& piece, GameArea& gameArea);
	void holdPiece(TetrisPiece& piece, GameArea gameArea);
	~GameController();
};