#pragma once
#include "TetrisBlock.h";

class TetrisPiece
{
public:
	TetrisPiece(std::vector<TetrisBlock>& blocks);

	void movePiece(sf::Vector2f amountToMove);
	void update(sf::RenderWindow& window);

	~TetrisPiece();

private:
	std::vector<TetrisBlock> blocks;
};