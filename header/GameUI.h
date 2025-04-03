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

void initUI();
void displayGameUI(sf::RenderWindow& window);

/// <summary>
/// Location of the holding box relative to the screen.
/// </summary>
sf::Vector2f holdBoxLocation;

inline void initUI()
{
	// set the string to display
	holdBoxText.setString("Hold");

	// set the character size
	holdBoxText.setCharacterSize(24); // in pixels, not points!

	// set the color
	holdBoxText.setFillColor(sf::Color::Red);

	// set the text style
	holdBoxText.setStyle(sf::Text::Bold);
	sf::FloatRect rect = holdBoxText.getGlobalBounds();
	holdBoxText.setPosition(gameAreaPosition - sf::Vector2f(rect.size.x, 0));

	nextText.setPosition(gameAreaPosition + sf::Vector2f(gameAreaDimensions.x * blockSize, 0));
	nextText.setString("Next");
	nextText.setCharacterSize(24);

	sf::Vector2f padding = sf::Vector2f(0, 10);

	holdBoxShape.setSize(sf::Vector2f(125, 125));
	holdBoxShape.setOutlineThickness(-5);
	holdBoxShape.setOutlineColor(sf::Color::Red);
	holdBoxShape.setFillColor(sf::Color::Transparent);
	holdBoxShape.setPosition(sf::Vector2f(gameAreaPosition.x - holdBoxShape.getSize().x, gameAreaPosition.y) + sf::Vector2f(0, rect.size.y) + padding);
	holdBoxLocation = holdBoxShape.getPosition() + sf::Vector2f(holdBoxShape.getSize().x / 8, holdBoxShape.getSize().y / 4);

	sf::FloatRect nextTextRect = nextText.getGlobalBounds();

	nextShapeBox.setSize(sf::Vector2f(125, 450));
	nextShapeBox.setPosition(sf::Vector2f(nextText.getPosition().x, nextText.getPosition().y + nextTextRect.size.y) + padding);
	nextShapeBox.setOutlineColor(sf::Color::White);
	nextShapeBox.setOutlineThickness(-5);
	nextShapeBox.setFillColor(sf::Color::Transparent);

	int previewPieceSize = 18;
	int verticalPaddingNextPreview = 20;
	for (int i = 0; i < 6; i++)
	{
		previewPieces.push_back(getNewTetramino(nextShapeBox.getPosition() + sf::Vector2f(nextShapeBox.getSize().x / 3, 0) + sf::Vector2f(0, i * 75 + verticalPaddingNextPreview), previewPieceSize));
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
	}
}
