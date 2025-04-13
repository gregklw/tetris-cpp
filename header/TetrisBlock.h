#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

extern const int gameAreaBlockSize;
extern const sf::Vector2f gameAreaPosition;
extern const sf::Color blockBorderColor;

class TetrisBlock
{
public:
	TetrisBlock(sf::Vector2f startGridPosition, sf::Vector2f startScreenPosition, sf::Color color, int size);
	void update(sf::RenderWindow& window);
	//void moveBlockByGrid(sf::Vector2f gridPosition);
	void moveBlock(sf::Vector2f amount);
	void setPosition(sf::Vector2f position);
	//void setGridPosition(sf::Vector2f position);
	void setBlockSize(int newBlockSize);
	void printBlock();
	//sf::Vector2f getGridPosition();
	sf::Vector2f getBlockStartGridPos();
	sf::RectangleShape blockShape;
	~TetrisBlock();

private:
	//sf::Vector2f gridPosition;
	sf::Vector2f blockPosition;
	sf::Vector2f blockStartGridPos;
};