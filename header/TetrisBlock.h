#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

extern int blockSize;

class TetrisBlock
{
public:
	TetrisBlock(sf::Vector2f startPosition, sf::Color color);
	void update(sf::RenderWindow& window);
	void moveBlock(sf::Vector2f position);
	void setBlockPosition(sf::Vector2f& blockPosition);
	sf::Vector2f getBlockPosition();
	sf::RectangleShape blockShape;
	~TetrisBlock();
	
private:
	sf::Vector2f blockPosition;
};