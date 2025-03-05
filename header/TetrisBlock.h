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
	void moveBlock(sf::Vector2f position);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getGridPosition();
	sf::RectangleShape blockShape;
	~TetrisBlock();
	
private:
	sf::Vector2f gridPosition;
	sf::Vector2f blockPosition;
};