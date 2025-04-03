#pragma once
#include "TetrisBlock.h";

class TetrisPiece
{
public:
	TetrisPiece();
	TetrisPiece(std::array<sf::Vector2f, 4> blockPivots, sf::Vector2f screenStartPosition, sf::Color color, int blockSize);
	std::vector<TetrisBlock> blocks;
	void setPosition(sf::Vector2f position);
	//void setGridPosition(sf::Vector2f targetPosition);
	//void movePieceByGrid(sf::Vector2f gridPosition);
	void movePiece(sf::Vector2f amount);
	void setSize(sf::Vector2f size);
	void update(sf::RenderWindow& window);
	void printPiece();
	~TetrisPiece();

private:
};