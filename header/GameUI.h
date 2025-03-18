#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisPiece.h"

sf::RectangleShape previewPanel;
sf::Font font("../fonts/tetra.ttf");

//Holding box UI
sf::Text holdBoxText(font); // a font is required to make a text object
sf::RectangleShape holdBoxShape;

//Next Piece Preview UI
sf::Text nextText(font);
sf::RectangleShape nextShapeBox;

//extern TetrisPiece heldPiece;
extern sf::Vector2f gameAreaDimensions;

std::vector<TetrisPiece> previewPieces;

void init();
void displayGameUI(sf::RenderWindow& window);

inline void init()
{
	//heldPiece.setPiecePosition(holdBoxShape.getPosition());
	// set the string to display
	holdBoxText.setString("Hold");

	// set the character size
	holdBoxText.setCharacterSize(24); // in pixels, not points!

	// set the color
	holdBoxText.setFillColor(sf::Color::Red);

	// set the text style
	holdBoxText.setStyle(sf::Text::Bold);
	sf::FloatRect rect = holdBoxText.getGlobalBounds();
	holdBoxText.setPosition(gameAreaStartPosition - sf::Vector2f(rect.size.x, 0));

	nextText.setPosition(gameAreaStartPosition + sf::Vector2f(gameAreaDimensions.x * blockSize, 0));
	nextText.setString("Next");
	nextText.setCharacterSize(24);

	sf::Vector2f padding = sf::Vector2f(0,10);

	holdBoxShape.setSize(sf::Vector2f(125, 125));
	holdBoxShape.setOutlineThickness(-5);
	holdBoxShape.setOutlineColor(sf::Color::Red);
	holdBoxShape.setFillColor(sf::Color::Transparent);
	holdBoxShape.setPosition(sf::Vector2f(gameAreaStartPosition.x - holdBoxShape.getSize().x, gameAreaStartPosition.y) + sf::Vector2f(0, rect.size.y) + padding);

	sf::FloatRect nextTextRect = nextText.getGlobalBounds();

	nextShapeBox.setSize(sf::Vector2f(125, 450));
	nextShapeBox.setPosition(sf::Vector2f(nextText.getPosition().x, nextText.getPosition().y + nextTextRect.size.y) + padding);
	nextShapeBox.setOutlineColor(sf::Color::White);
	nextShapeBox.setOutlineThickness(-5);
	nextShapeBox.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < 6; i++)
	{
		previewPieces.push_back(getNewPiece());
	}

	for (int i = 0; i < previewPieces.size(); i++)
	{
		previewPieces[i].setScreenPosition(nextShapeBox.getPosition() + sf::Vector2f(0, i * 100));
		
	}
}

inline void displayGameUI(sf::RenderWindow& window)
{
	// inside the main loop, between window.clear() and window.display()
	window.draw(holdBoxText);
	window.draw(holdBoxShape);
	window.draw(nextText);
	window.draw(nextShapeBox);
	if (heldPiecePointer != nullptr) heldPiece.update(window);
	for (int i = 0; i < previewPieces.size(); i++)
	{
		previewPieces[i].update(window);
		previewPieces[i].setSize(sf::Vector2f(12, 12));
		/*for (int j = 0; j < previewPieces[i].blocks.size(); j++)
		{
			std::cout << previewPieces[i].blocks[j].blockShape.getPosition().x << "|" << previewPieces[i].blocks[j].blockShape.getPosition().y << "\n";
		}*/
	}
}
