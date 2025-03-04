#pragma once
#include <SFML/Window.hpp>
#include "TetrisPiece.h"
#include "GameArea.h"

class GameController
{
public:
	GameController();
	bool hardDroppedOnPress;
	bool rotateOnPress;
	void hardDropPiece(TetrisPiece& piece, GameArea& gameArea);
	void rotatePiece(TetrisPiece& piece, GameArea& gameArea);
	void checkLandedOnPieceBelow(TetrisPiece& piece, GameArea& gameArea);
	void movePieceLeft(TetrisPiece& piece, GameArea& gameArea);
	void movePieceRight(TetrisPiece& piece, GameArea& gameArea);
	void movePieceDown(TetrisPiece& piece, GameArea& gameArea);
	~GameController();
};