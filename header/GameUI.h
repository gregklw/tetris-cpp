#pragma once
#include <SFML/Graphics.hpp>

sf::RectangleShape previewPanel;
sf::Font font("../fonts/tetra.ttf");
sf::Text holdBoxText(font); // a font is required to make a text object
sf::Text nextText(font);

void init();
void displayGameUI(sf::RenderWindow& window);

inline void init()
{

}

inline void displayGameUI(sf::RenderWindow& window)
{

	// set the string to display
	holdBoxText.setString("Hold");

	// set the character size
	holdBoxText.setCharacterSize(24); // in pixels, not points!

	// set the color
	holdBoxText.setFillColor(sf::Color::Red);

	// set the text style
	holdBoxText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	sf::FloatRect rect = holdBoxText.getGlobalBounds();
	holdBoxText.setPosition(gameAreaStartPosition - sf::Vector2f(rect.size.x, 0));

	nextText.setPosition(gameAreaStartPosition + sf::Vector2f(gameAreaDimensions.x * blockSize, 0));
	nextText.setString("Next");
	nextText.setCharacterSize(24);

	// inside the main loop, between window.clear() and window.display()
	window.draw(holdBoxText);
	window.draw(nextText);
}
