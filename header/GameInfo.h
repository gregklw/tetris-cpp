#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisPiece.h"

int blockSize = 25;
int dropTimerCooldown = 10;
int sensitivityCooldown = 1;
sf::Vector2f gameAreaDimensions(10, 20);
sf::Color occupiedBorderColor = sf::Color::Black;
sf::Color gameBackgroundColor = sf::Color(26,5,110);
sf::Color emptyBorderColor = gameBackgroundColor;

/// <summary>
/// List of tetraminos used for randomizing new shape for player.
/// First member of array is always pivot.
/// </summary>
std::vector<TetrisPiece> tetraminoList
{
	std::vector<TetrisPiece>{

		//line
		TetrisPiece(
		std::array<sf::Vector2f, 4> 
		{
			sf::Vector2f(2,0),
			sf::Vector2f(0,0),
			sf::Vector2f(1,0),
			sf::Vector2f(3,0)
		}
		, sf::Color(3, 194, 252)
		),

		//J-shape
		TetrisPiece(
		std::array<sf::Vector2f, 4>
		{
			sf::Vector2f(1,1),
			sf::Vector2f(0,0),
			sf::Vector2f(0,1),
			sf::Vector2f(2,1)
		}
		, sf::Color(0, 4, 240)
		),

		//L-shape
		TetrisPiece(
		std::array<sf::Vector2f, 4>
		{
			sf::Vector2f(1,1),
			sf::Vector2f(2,0),
			sf::Vector2f(0,1),
			sf::Vector2f(2,1)
		}
		, sf::Color(255, 205, 5)
		),

		//box shape
		TetrisPiece(
		std::array<sf::Vector2f, 4>
		{
			sf::Vector2f(0,0),
			sf::Vector2f(0,1),
			sf::Vector2f(1,0),
			sf::Vector2f(1,1)
		}
		, sf::Color(238, 255, 0)
		),

		//s-shape
		TetrisPiece(
		std::array<sf::Vector2f, 4>
		{
			sf::Vector2f(1,0),
			sf::Vector2f(2,0),
			sf::Vector2f(0,1),
			sf::Vector2f(1,1)
		}
		, sf::Color(0, 255, 26)
		),

		//t-shape
		TetrisPiece(
		std::array<sf::Vector2f, 4>
		{
			sf::Vector2f(1,0),
			sf::Vector2f(0,1),
			sf::Vector2f(1,1),
			sf::Vector2f(2,1)
		}
		, sf::Color(149, 7, 181)
		),

		//z-shape
		TetrisPiece(
		std::array<sf::Vector2f, 4>
		{
			sf::Vector2f(1,1),
			sf::Vector2f(0,0),
			sf::Vector2f(1,0),
			sf::Vector2f(2,1)
		}
		, sf::Color(255, 25, 52)
		)

	}
};
