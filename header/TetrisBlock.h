#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

extern int blockSize;
extern sf::Vector2f gameAreaStartPosition;
extern sf::Color blockBorderColor;

class TetrisBlock
{
public:
	TetrisBlock(sf::Vector2f startGridPosition, sf::Color color);
	void update(sf::RenderWindow& window);
	void moveBlockByScreenPosition(sf::Vector2f position);
	void setScreenPosition(sf::Vector2f position);
	void moveBlockByGridPosition(sf::Vector2f position);
	void setGridPosition(sf::Vector2f position);
	void setBlockSize(int newBlockSize);
	sf::Vector2f getGridPosition();
	sf::RectangleShape blockShape;
	~TetrisBlock();
	
private:
	int currentBlockSize;
	sf::Vector2f gridPosition;
	sf::Vector2f blockPosition;
};