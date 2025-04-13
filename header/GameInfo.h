#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisPiece.h"

const int gameAreaBlockSize = 25;
const int autoMoveDownCooldown = 15;
const int sensitivityCooldown = 1;
const sf::Vector2f gameAreaPosition(125, 100);
const sf::Vector2f pieceGridSpawnPosition(4, 0);
const sf::Vector2f pieceSpawnPosition(gameAreaPosition);
const sf::Vector2f gameAreaDimensions = sf::Vector2f(10, 20);
const sf::Color occupiedBorderColor = sf::Color::Black;
const sf::Color gameAreaBackgroundColor = sf::Color(26, 5, 110);
const sf::Color ghostFillColor = sf::Color::Transparent;
const sf::Color emptyBorderColor = gameAreaBackgroundColor;
const sf::Color blockBorderColor = sf::Color(125, 125, 125);

/// <summary>
/// Piece that is used for display when being held.
/// </summary>
TetrisPiece heldPiece;
TetrisPiece* heldPiecePointer = nullptr;

/// <summary>
/// Boolean to mark whether a hard drop action has been performed.
/// </summary>
bool hardDroppedOnPress = false;

/// <summary>
/// Boolean to mark whether a rotate action has been performed.
/// </summary>
bool rotateOnPress = false;

/// <summary>
/// Boolean to mark whether a hold piece action has been performed.
/// </summary>
bool holdPieceOnPress = false;

/// <summary>
/// List of tetraminos used for randomizing new shape for player.
/// First member of array is always pivot.
/// </summary>
TetrisPiece getNewTetramino(sf::Vector2f screenStartPosition, int size)
{
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
		, screenStartPosition

		, sf::Color(3, 194, 252)
			, size
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
			, screenStartPosition
			, sf::Color(0, 4, 240)
				, size
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
			, screenStartPosition
			, sf::Color(252, 152, 3)
				, size
			),

			//box shape
			TetrisPiece(
			std::array<sf::Vector2f, 4>
			{
				sf::Vector2f(1,1),
				sf::Vector2f(0,0),
				sf::Vector2f(0,1),
				sf::Vector2f(1,0)
			}
			, screenStartPosition
			, sf::Color(238, 255, 0)
				, size
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
			, screenStartPosition
			, sf::Color(0, 255, 26)
				, size
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
			, screenStartPosition
			, sf::Color(149, 7, 181)
				, size
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
			, screenStartPosition
			, sf::Color(255, 25, 52)
				, size
			)

		}
	};

	TetrisPiece newPiece = tetraminoList[std::rand() % tetraminoList.size()];
	//newPiece.setGridPosition(pieceGridSpawnPosition);
	return newPiece;
}