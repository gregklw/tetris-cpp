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

const int previewPieceSize = 18;

void initUI();
void displayGameUI(sf::RenderWindow& window);

//extern TetrisPiece heldPiece;
extern const sf::Vector2f gameAreaDimensions;
extern GameArea gameArea;

//std::vector<TetrisPiece> previewPieces;


/// <summary>
/// Location of the holding box relative to the screen.
/// </summary>
sf::Vector2f holdBoxLocation;

//Score Display
sf::Text scoreText(font);

inline void setupText(sf::Text& text, const sf::String& startString, unsigned int characterSize, sf::Color textFillColor = sf::Color::White, uint32_t style = sf::Text::Regular)
{
	// set the string to display
	text.setString(startString);

	// set the character size
	text.setCharacterSize(characterSize); // in pixels, not points!

	// set the color
	text.setFillColor(textFillColor);

	// set the text style
	text.setStyle(style);
}

inline void setupBox(sf::RectangleShape& shape, sf::Vector2f size, float outlineThickness, sf::Color outlineColor, sf::Color fillColor)
{
	// set the string to display
	shape.setSize(size);

	// set the character size
	shape.setOutlineThickness(outlineThickness); // in pixels, not points!

	// set the color
	shape.setFillColor(fillColor);
	shape.setOutlineColor(outlineColor);
}

inline void initUI()
{
	setupText(holdBoxText, "Hold", 24, sf::Color::Red, sf::Text::Bold);

	sf::FloatRect holdBoxTextRect = holdBoxText.getGlobalBounds();
	holdBoxText.setPosition(gameAreaPosition - sf::Vector2f(holdBoxTextRect.size.x * 1.75, 0));

	sf::Vector2f padding = sf::Vector2f(0, 10);
	setupBox(holdBoxShape, sf::Vector2f(125, 125), -5, sf::Color::Red, sf::Color::Transparent);
	holdBoxShape.setPosition(sf::Vector2f(gameAreaPosition.x - holdBoxShape.getSize().x, gameAreaPosition.y) + sf::Vector2f(0, holdBoxTextRect.size.y) + padding);
	holdBoxLocation = holdBoxShape.getPosition() + sf::Vector2f(holdBoxShape.getSize().x / 8, holdBoxShape.getSize().y / 4);

	setupBox(nextShapeBox, sf::Vector2f(125, 450), -5, sf::Color::White, sf::Color::Transparent);
	sf::Vector2f gameAreaRightAnchor = gameAreaPosition + sf::Vector2f(gameAreaDimensions.x * gameAreaBlockSize, 0);
	
	setupText(nextText, "Next", 24);
	nextText.setPosition(gameAreaRightAnchor + sf::Vector2f(125 / 3, 0));

	sf::FloatRect nextTextRect = nextText.getGlobalBounds();
	nextShapeBox.setPosition(gameAreaRightAnchor + sf::Vector2f(0, nextTextRect.size.y) + padding);

	//for (int i = 0; i < gameArea.nextPieces.size(); i++)
	//{
	//	//previewPieces.push_back(getNewTetramino(nextShapeBox.getPosition() + sf::Vector2f(nextShapeBox.getSize().x / 3, 0) + sf::Vector2f(0, i * 75 + verticalPaddingNextPreview), previewPieceSize));
	//	gameArea.nextPieces[i].setPosition(nextShapeBox.getPosition() + sf::Vector2f(nextShapeBox.getSize().x / 3, 0) + sf::Vector2f(0, i * 75 + verticalPaddingNextPreview));
	//	gameArea.nextPieces[i].setSize(sf::Vector2f(previewPieceSize, previewPieceSize));
	//}

}

inline void displayGameUI(sf::RenderWindow& window)
{
	// inside the main loop, between window.clear() and window.display()
	window.draw(holdBoxText);
	window.draw(holdBoxShape);
	window.draw(nextText);
	window.draw(nextShapeBox);
	if (heldPiecePointer != nullptr) heldPiece.update(window);

	int verticalPaddingNextPreview = 20;
	for (int i = 0; i < gameArea.nextPieces.size(); i++)
	{
		gameArea.nextPieces[i].setPosition(nextShapeBox.getPosition() + sf::Vector2f(nextShapeBox.getSize().x / 3, 0) + sf::Vector2f(0, i * 75 + verticalPaddingNextPreview));
		gameArea.nextPieces[i].setSize(sf::Vector2f(previewPieceSize, previewPieceSize));
		gameArea.nextPieces[i].update(window);
	}
}
