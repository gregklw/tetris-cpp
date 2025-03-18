#pragma once
#include "TetrisBlock.h";

class TetrisPiece
{
public:
	TetrisPiece();
	TetrisPiece(std::array<sf::Vector2f, 4> blockIndices, sf::Color color, int blockSize);
	std::vector<TetrisBlock> blocks;
	void setScreenPosition(sf::Vector2f position);
	void setGridPosition(sf::Vector2f amountToMoveInGrid);
	void setSize(sf::Vector2f size);
	void movePieceByGridPosition(sf::Vector2f amountToMoveInGrid);
	void update(sf::RenderWindow& window);
	~TetrisPiece();

private:
};