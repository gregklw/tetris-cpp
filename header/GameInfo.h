#pragma once
#include <SFML/Graphics.hpp>
#include "TetrisPiece.h"

int blockSize = 25;
int dropTimerCooldown = 10;
int sensitivityCooldown = 1;
sf::Vector2f gameAreaStartPosition(125, 100);
sf::Vector2f gameAreaDimensions = sf::Vector2f(10, 20);
sf::Color occupiedBorderColor = sf::Color::Black;
sf::Color gameAreaBackgroundColor = sf::Color(26,5,110);
sf::Color emptyBorderColor = gameAreaBackgroundColor;
sf::Color blockBorderColor = sf::Color(125, 125, 125);

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
/// Location of the holding box relative to the screen.
/// </summary>
sf::Vector2f holdBoxLocation(-3, 4);

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
			, blockSize
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
			, blockSize
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
		, sf::Color(252, 152, 3)
			, blockSize
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
		, sf::Color(238, 255, 0)
			, blockSize
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
			, blockSize
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
			, blockSize
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
			, blockSize
		)

	}
};

TetrisPiece getNewPiece();

inline inline TetrisPiece getNewPiece()
{
	TetrisPiece newPiece = tetraminoList[std::rand() % tetraminoList.size()];
	//std::vector newBlocks = newPiece.blocks;
	//for (int i = 0; i < newBlocks.size(); i++)
	//{
	//	newBlocks[i].moveBlock(gameAreaStartPosition);
	//	//std::cout << newBlocks[i].getBlockPosition().x << ", " << newBlocks[i].getBlockPosition().y << "\n";
	//}
	//newPiece.blocks = newBlocks;
	return newPiece;
}


