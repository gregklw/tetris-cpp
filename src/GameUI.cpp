#include "../header/GameUI.h"

GameUI::GameUI() : holdBoxText(font), nextText(font), scoreText(font)
{
	font = sf::Font("../fonts/arial.ttf");

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

	setupText(scoreText, "Score: ", 24);
	__hook(&TetrisEvents::OnTetrisLineClear, &tetrisEvents, &GameUI::updateScore);
}

void::GameUI::displayGameUI(sf::RenderWindow& window)
{
	// inside the main loop, between window.clear() and window.display()
	window.draw(holdBoxText);
	window.draw(holdBoxShape);
	window.draw(nextText);
	window.draw(nextShapeBox);
	window.draw(scoreText);
	if (heldPiecePointer != nullptr) heldPiece.update(window);

	int verticalPaddingNextPreview = 20;
	for (int i = 0; i < nextPieces.size(); i++)
	{
		nextPieces[i].setPosition(nextShapeBox.getPosition() + sf::Vector2f(nextShapeBox.getSize().x / 3, 0) + sf::Vector2f(0, i * 75 + verticalPaddingNextPreview));
		nextPieces[i].setSize(sf::Vector2f(previewPieceSize, previewPieceSize));
		nextPieces[i].update(window);
	}
}

void GameUI::updateScore()
{
	std::string scoreStr = "Score: " + std::to_string(currentScore);
	scoreText.setString(scoreStr);
}

GameUI::~GameUI()
{
	__unhook(&TetrisEvents::OnTetrisLineClear, &tetrisEvents, &GameUI::updateScore);
}

void GameUI::setupText(sf::Text& text, const sf::String& startString, unsigned int characterSize, sf::Color textFillColor, uint32_t style)
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

void GameUI::setupBox(sf::RectangleShape& shape, sf::Vector2f size, float outlineThickness, sf::Color outlineColor, sf::Color fillColor)
{
	// set the string to display
	shape.setSize(size);

	// set the character size
	shape.setOutlineThickness(outlineThickness); // in pixels, not points!

	// set the color
	shape.setFillColor(fillColor);
	shape.setOutlineColor(outlineColor);
}
