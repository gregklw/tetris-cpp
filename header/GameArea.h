#pragma once
#include <SFML/Graphics.hpp>

extern int blockSize;

class GameArea
{
public:
	GameArea();
	void update(sf::RenderWindow& window);
	~GameArea();
private:
	sf::RectangleShape gameAreaVisual;
};