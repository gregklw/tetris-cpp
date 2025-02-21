#pragma once
#include <SFML/Graphics.hpp>

extern int blockSize;

class TetrisBlock
{
public:
	TetrisBlock(sf::Vector2f startPosition, sf::Color color);
	void update(sf::RenderWindow& window);
	void moveBlock(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	~TetrisBlock();
	
private:
	sf::RectangleShape blockShape;
	sf::Vector2f position;
	sf::Vector2f size;
};