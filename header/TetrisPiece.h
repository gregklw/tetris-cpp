#pragma once
#include "TetrisBlock.h";

class TetrisPiece
{
public:
	TetrisPiece(sf::Color color);
	std::vector<TetrisBlock> blocks;
	void moveLeft();
	void moveRight();
	void moveDown();
	void update(sf::RenderWindow& window);

	~TetrisPiece();

private:
	void movePiece(sf::Vector2f amountToMove);
};