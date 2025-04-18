#include "../header/GameArea.h"

GameArea::GameArea(sf::Vector2f startPosition)
{
	__hook(&TetrisEvents::OnTetrisLineClear, &tetrisEvents, &GameArea::addToScore);

	autoMoveDownTimer = 0;
	gameAreaVisual.setPosition(startPosition);
	gameAreaVisual.setOutlineThickness(-gameAreaBlockSize / 10.0f);
	gameAreaVisual.setOutlineColor(emptyBorderColor);
	gameAreaVisual.setFillColor(gameAreaBackgroundColor);
	gameAreaVisual.setSize(sf::Vector2f(gameAreaDimensions.x * gameAreaBlockSize, gameAreaDimensions.y * gameAreaBlockSize));

	resetGame();

	//printGridPositions();
}

void GameArea::update(sf::RenderWindow& window)
{
	//printGridPositions();
	window.draw(gameAreaVisual);
	for (int y = 0; y < gameAreaDimensions.y; y++)
	{
		for (int x = 0; x < gameAreaDimensions.x; x++)
		{
			grid[y][x].draw(window);
		}
	}
	autoMoveCurrentPieceDown();
	previewHardDrop(window);
	currentPiece.update(window);
}

void GameArea::moveGridPoints(std::vector<sf::Vector2f>& gridPoints, sf::Vector2f amount)
{

	for (int i = 0; i < gridPoints.size(); i++)
	{
		gridPoints[i] += amount;
	}
}

void GameArea::setGridPoints(std::vector<sf::Vector2f>& gridPoints, std::vector<sf::Vector2f> newGridPoints)
{
	for (int i = 0; i < gridPoints.size(); i++)
	{
		gridPoints[i] = newGridPoints[i];
	}
}

void GameArea::previewHardDrop(sf::RenderWindow& window)
{
	ghostPiece = TetrisPiece(currentPiece);
	setGridPoints(ghostGridPositions, currentGridPositions);

	for (int i = 0; i < ghostPiece.blocks.size(); i++)
	{
		ghostPiece.blocks[i].blockShape.setFillColor(ghostFillColor);
	}
	movePieceDownToLowestPoint(ghostPiece, ghostGridPositions);
	ghostPiece.update(window);
}

bool GameArea::checkHorizontalCollision(std::vector<sf::Vector2f> gridPoints, sf::Vector2f velocity)
{
	for (int i = 0; i < gridPoints.size(); i++)
	{
		int gridPosX = gridPoints[i].x;
		int gridPosY = gridPoints[i].y;

		//-------check if piece is touching left wall moving left
		if (velocity.x < 0)
		{
			if (gridPosX == 0 || grid[gridPosY][gridPosX - 1].occupied)
			{
				return true;
			}
		}
		//-------check if piece is touching right wall moving right
		else if (velocity.x > 0)
		{
			if (gridPosX == gameAreaDimensions.x - 1 || grid[gridPosY][gridPosX + 1].occupied)
			{
				return true;
			}
		}
	}

	return false;
}

bool GameArea::checkVerticalCollision(std::vector<sf::Vector2f> gridPoints)
{
	for (int i = 0; i < gridPoints.size(); i++)
	{
		int gridPosX = gridPoints[i].x;
		int gridPosY = gridPoints[i].y;

		//-------check if piece is touching bottom
		if (gridPosY == gameAreaDimensions.y - 1)
		{
			/*std::cout << "Current height: " << gridPosY << "|" << "Bottom of game area height: " << gameAreaDimensions.y - 1 << "\n";
			std::cout << "Collided with bottom of game area" << "\n";*/
			return true;
		}

		//-------check if piece is touching occupied area below it
		for (int x = 0; x < grid[gridPosY].size(); x++)
		{
			if (gridPosX == grid[gridPosY][x].gridPosX && grid[gridPosY + 1][x].occupied)
			{
				//std::cout << "Collided with top of occupied spot" << "\n";
				return true;
			}
		}
	}
	return false;
}

void GameArea::occupyCells(TetrisPiece piece)
{
	for (int i = 0; i < piece.blocks.size(); i++)
	{
		grid[currentGridPositions[i].y][currentGridPositions[i].x].occupyCell(piece.blocks[i].blockShape.getFillColor());
	}
}

void GameArea::checkAndClearRow(int lowestRowToStart)
{
	if (lowestRowToStart < 0) return;

	bool assertCompleteRow = true;
	//loop to check if any one of the cells are not occupied
	for (int j = 0; j < grid[lowestRowToStart].size(); j++)
	{
		if (!grid[lowestRowToStart][j].occupied)
		{

			assertCompleteRow = false;
			break;
		}
	}
	//if row is complete then clear it and move all the other stuff above it down
	if (assertCompleteRow)
	{
		__raise tetrisEvents.OnTetrisLineClear();
		clearRow(lowestRowToStart);
		moveRowsDownAfterClearing(lowestRowToStart);
	}
	else
	{
		lowestRowToStart--;
	}

	checkAndClearRow(lowestRowToStart);
}

void GameArea::clearRow(int row)
{
	for (int i = 0; i < grid[row].size(); i++)
	{
		grid[row][i].clearCell();
	}
}

void GameArea::updateGameAfterVerticalCollision(TetrisPiece piece)
{


	occupyCells(piece);
	int lowestRowToStart = 0;

	for (int i = 0; i < piece.blocks.size(); i++)
	{
		int gridPosY = currentGridPositions[i].y;
		if (lowestRowToStart < gridPosY)
		{
			lowestRowToStart = gridPosY;
		}
	}
	checkAndClearRow(lowestRowToStart);
	spawnTetraminoOnGameArea(grabTopPreviewPiece());
}

void GameArea::moveRowsDownAfterClearing(int clearedRow)
{
	std::cout << clearedRow << "number\n";
	while (clearedRow >= 1)
	{
		std::cout << clearedRow << " CLEARED\n";
		//go through each member and move it down to target row

		for (int i = 0; i < grid[clearedRow].size(); i++)
		{
			std::cout << clearedRow << " ROWS BEING MOVED\n";
			grid[clearedRow][i].copyCell(grid[clearedRow - 1][i]);
			grid[clearedRow - 1][i].clearCell();
		}
		clearedRow--;
	}
}

void GameArea::movePieceDownToLowestPoint(TetrisPiece& piece, std::vector<sf::Vector2f>& gridPoints)
{
	while (!checkVerticalCollision(gridPoints))
	{
		movePieceDown(piece, gridPoints);
	}
}

void GameArea::rotatePiece()
{
	if (rotateOnPress) return;

	std::vector<TetrisBlock>& targetBlocks = currentPiece.blocks;
	sf::Vector2f currentBlockSize = currentPiece.blocks[0].blockShape.getSize();

	for (int i = 0; i < targetBlocks.size(); i++)
	{
		sf::Vector2f pivotPos(currentGridPositions[i].x, currentGridPositions[i].y);
		std::vector<sf::Vector2f> newPoints;
		bool isObstructed = false;

		for (int j = 0; j < targetBlocks.size(); j++)
		{
			sf::Vector2f oldPos(currentGridPositions[j].x, currentGridPositions[j].y);

			float newX = -(oldPos.y - pivotPos.y) + pivotPos.x;
			float newY = oldPos.x - pivotPos.x + pivotPos.y;


			if (newX < 0 || newX >= gameAreaDimensions.x || newY < 0 || newY >= gameAreaDimensions.y || grid[newY][newX].occupied)
			{
				isObstructed = true;
			}

			newPoints.push_back(sf::Vector2f(newX, newY));

			/*# rotates the shape clockwise
				def rotateCW(self) :
				newBlockX = [0, 0, 0, 0]
				newBlockY = [0, 0, 0, 0]
				#rotate all of the blocks
				for i in range(self.numblocks) :
					newBlockX[i] = -(self.blockList[i].gridYpos - self.blockList[0].gridYpos) +
					self.blockList[0].gridXpos
					newBlockY[i] = (self.blockList[i].gridXpos - self.blockList[0].gridXpos) +
					self.blockList[0].gridYpos
					self.blockList[i].gridXpos = newBlockX[i]
					self.blockList[i].gridYpos = newBlockY[i]*/
		}

		//if not obstructed then apply the new rotation points and end this function
		if (!isObstructed)
		{
			for (int j = 0; j < newPoints.size(); j++)
			{
				currentPiece.blocks[j].setPosition(gameAreaPosition + sf::Vector2f(newPoints[j].x * currentBlockSize.x, newPoints[j].y * currentBlockSize.y));
			}
			setGridPoints(currentGridPositions, newPoints);
			//printGridPositions();
			break;
		}
		//otherwise if its obstructed and if counter isn't exceeding the block size then try the next block as a pivot point
	}
	//printGridPositions();
}

void GameArea::movePieceLeft()
{
	int leftAmount = -1;
	//std::cout << "Horizontal Collision Left: " << checkHorizontalCollision(currentPiece, sf::Vector2f(leftAmount * blockSize, 0)) << "\n";
	if (!checkHorizontalCollision(currentGridPositions, sf::Vector2f(leftAmount * gameAreaBlockSize, 0)))
	{
		currentPiece.movePiece(sf::Vector2f(leftAmount * gameAreaBlockSize, 0));
		moveGridPoints(currentGridPositions, sf::Vector2f(leftAmount, 0));
		//printGridPositions();
	}
}

void GameArea::movePieceRight()
{
	int rightAmount = 1;
	//std::cout << "Horizontal Collision Right: " << checkHorizontalCollision(currentPiece, sf::Vector2f(rightAmount * blockSize, 0)) << "\n";
	if (!checkHorizontalCollision(currentGridPositions, sf::Vector2f(rightAmount * gameAreaBlockSize, 0)))
	{
		currentPiece.movePiece(sf::Vector2f(rightAmount * gameAreaBlockSize, 0));
		moveGridPoints(currentGridPositions, sf::Vector2f(rightAmount, 0));
		//printGridPositions();
	}
}

void GameArea::movePieceDown(TetrisPiece& piece, std::vector<sf::Vector2f>& gridPositions)
{
	int downAmount = 1;
	piece.movePiece(sf::Vector2f(0, downAmount * gameAreaBlockSize));
	moveGridPoints(gridPositions, sf::Vector2f(0, downAmount));
}

void GameArea::holdPiece()
{
	if (!holdPieceOnPress)
	{
		TetrisPiece pieceToBeCached = TetrisPiece(currentPiece);
		std::cout << "----------------------------------------------------------------" << "\n";
		//currentPiece.printPiece();
		//if no piece was previously held
		if (heldPiecePointer == nullptr)
		{
			heldPiece = pieceToBeCached;
			heldPiecePointer = &heldPiece;
			spawnTetraminoOnGameArea(grabTopPreviewPiece());
		}
		else //otherwise if we're swapping pieces
		{
			currentPiece = TetrisPiece(heldPiece);
			heldPiece = pieceToBeCached;
		}
		//initializePiece(currentPiece);
		currentPiece.setPosition(pieceSpawnPosition);
		//piece.setGridPosition(pieceGridSpawnPosition);
		setGridPoints(currentGridPositions,

			std::vector<sf::Vector2f>
		{
			currentPiece.blocks[0].getBlockStartGridPos(),
				currentPiece.blocks[1].getBlockStartGridPos(),
				currentPiece.blocks[2].getBlockStartGridPos(),
				currentPiece.blocks[3].getBlockStartGridPos()
		}
		);

		heldPiece.setPosition(holdBoxLocation);
		std::cout << "****************************************************************" << "\n";
		currentPiece.printPiece();
		std::cout << "----------------------------------------------------------------" << "\n";
	}
}

void GameArea::moveCurrentPieceDown()
{
	if (!checkVerticalCollision(currentGridPositions))
	{
		movePieceDown(currentPiece, currentGridPositions);
	}
	else
	{
		//update game area
		updateGameAfterVerticalCollision(currentPiece);
		holdPieceOnPress = false;
	}
}

void GameArea::hardDropCurrentPiece()
{
	if (hardDroppedOnPress) return;

	movePieceDownToLowestPoint(currentPiece, currentGridPositions);
	updateGameAfterVerticalCollision(currentPiece);
	holdPieceOnPress = false;
}

void GameArea::addToScore()
{
	currentScore += 20;
	std::cout << "Current score:" << currentScore << "\n";
}

void GameArea::autoMoveCurrentPieceDown()
{
	if (autoMoveDownTimer > autoMoveDownCooldown)
	{
		moveCurrentPieceDown();
		autoMoveDownTimer = 0;
	}
	autoMoveDownTimer++;
}

bool GameArea::isToppedOut(std::vector<TetrisBlock> pieceBlocks)
{
	for (int i = 0; i < pieceBlocks.size(); i++)
	{
		if (grid[pieceBlocks[i].getBlockStartGridPos().y][pieceBlocks[i].getBlockStartGridPos().x].occupied)
		{
			return true;
		}
	}
	return false;
}

void GameArea::resetGame()
{
	currentGridPositions.clear();
	currentGridPositions.shrink_to_fit();

	ghostGridPositions.clear();
	ghostGridPositions.shrink_to_fit();

	nextPieces.clear();
	nextPieces.shrink_to_fit();

	grid.clear();
	grid.shrink_to_fit();



	for (int y = 0; y < gameAreaDimensions.y; y++)
	{
		std::vector<Cell> cellRow;
		grid.push_back(cellRow);
		for (int x = 0; x < gameAreaDimensions.x; x++)
		{
			grid[y].push_back(Cell(x, y, gameAreaPosition));
		}
	}

	spawnTetraminoOnGameArea(getNewTetramino(gameAreaPosition, gameAreaBlockSize));

	for (int i = 0; i < currentPiece.blocks.size(); i++)
	{
		TetrisBlock& block = currentPiece.blocks[i];
		currentGridPositions.push_back(block.getBlockStartGridPos());
		ghostGridPositions.push_back(block.getBlockStartGridPos());
		//std::cout << "Current block start pos: " << block.getBlockStartGridPos().x << "/" << block.getBlockStartGridPos().y << "\n";
	}

	for (int i = 0; i < 6; i++)
	{
		nextPieces.push_back(getNewTetramino(sf::Vector2f(0, 0), previewPieceSize));
	}
}

void GameArea::printGridPositions()
{
	std::cout << "****************************************************************" << "\n";
	for (int i = 0; i < currentGridPositions.size(); i++)
	{
		std::cout << "Current Grid Position: " << currentGridPositions[i].x << "/" << currentGridPositions[i].y << "\n";
		std::cout << "Current Grid Position: " << currentGridPositions[i].x << "/" << currentGridPositions[i].y << "\n";
	}
	std::cout << "****************************************************************" << "\n";
}

void GameArea::spawnTetraminoOnGameArea(TetrisPiece piece)
{
	//check if topped out
	if (isToppedOut(piece.blocks))
	{
		resetGame();
		return;
	}

	currentPiece = piece;
	//currentPiece = grabTopPreviewPiece();
	//currentPiece.setSize(sf::Vector2f(gameAreaBlockSize, gameAreaBlockSize));

	setGridPoints(currentGridPositions,
		std::vector<sf::Vector2f>{
		currentPiece.blocks[0].getBlockStartGridPos(),
			currentPiece.blocks[1].getBlockStartGridPos(),
			currentPiece.blocks[2].getBlockStartGridPos(),
			currentPiece.blocks[3].getBlockStartGridPos()
	}
	);
}

TetrisPiece GameArea::grabTopPreviewPiece()
{
	TetrisPiece topPiece = TetrisPiece(nextPieces.front());
	topPiece.setSize(sf::Vector2f(gameAreaBlockSize, gameAreaBlockSize));
	topPiece.setPosition(gameAreaPosition);
	nextPieces.erase(nextPieces.begin());
	nextPieces.push_back(getNewTetramino(sf::Vector2f(0, 0), previewPieceSize));
	return topPiece;
}

GameArea::~GameArea()
{
	__unhook(&TetrisEvents::OnTetrisLineClear, &tetrisEvents, &GameArea::addToScore);
}

