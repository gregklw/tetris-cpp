#include "../header/GameArea.h"

GameArea::GameArea()
{
	gameAreaVisual.setOutlineThickness(-5);
	gameAreaVisual.setOutlineColor(sf::Color::Red);
	gameAreaVisual.setFillColor(sf::Color::Black);
	gameAreaVisual.setSize(sf::Vector2f(10 * blockSize, 20 * blockSize));
}

void GameArea::update(sf::RenderWindow& window)
{
	window.draw(gameAreaVisual);
}

GameArea::~GameArea()
{
}
