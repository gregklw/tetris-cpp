#pragma once
#include "TetrisBlock.h";

class TetrisPiece
{
public:
	TetrisPiece(std::array<TetrisBlock, 4>& blocks);

	void movePiece(sf::Vector2f amountToMove);
	void update(sf::RenderWindow& window);

	~TetrisPiece();

private:
	std::array<TetrisBlock, 4> blocks;
};