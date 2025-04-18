#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisPiece.h"
#include "TetrisEvents.h"

//extern TetrisPiece heldPiece;
extern const sf::Vector2f gameAreaDimensions;
extern std::vector<TetrisPiece> nextPieces;
extern TetrisPiece heldPiece;
extern TetrisPiece* heldPiecePointer;
extern int currentScore;
extern TetrisEvents tetrisEvents;
extern const int previewPieceSize;
extern sf::Vector2f holdBoxLocation;

class GameUI
{
public:
	GameUI();
	sf::RectangleShape previewPanel;
	sf::Font font;

	//Holding box UI
	sf::Text holdBoxText; // a font is required to make a text object
	sf::RectangleShape holdBoxShape;

	//Next Piece Preview UI
	sf::Text nextText;
	sf::RectangleShape nextShapeBox;

	void displayGameUI(sf::RenderWindow& window);
	void updateScore();


	//std::vector<TetrisPiece> previewPieces;

	//Score Display
	sf::Text scoreText;
	~GameUI();

private:
	void setupText(sf::Text& text, const sf::String& startString, unsigned int characterSize, sf::Color textFillColor = sf::Color::White, uint32_t style = sf::Text::Regular);
	void setupBox(sf::RectangleShape& shape, sf::Vector2f size, float outlineThickness, sf::Color outlineColor, sf::Color fillColor);
};