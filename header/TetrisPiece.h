#pragma once
#include "TetrisBlock.h";

class TetrisPiece
{
public:
	TetrisPiece(std::array<sf::Vector2f, 4> blockIndices, sf::Color color);
	std::vector<TetrisBlock> blocks;
	void movePiece(sf::Vector2f amountToMove);
	void update(sf::RenderWindow& window);
	~TetrisPiece();

private:
};