#include "GameLogic.h"

GameLogic::GameLogic(std::vector<std::vector < Symbol > > *Matrix, Symbol *winner, int *inaRow) {
	currentPlayer = X;
	SymbolMatrix = Matrix;
	matrixSize = SymbolMatrix->size();
	row.resize(matrixSize, 0);
	col.resize(matrixSize, 0);
	diagonal = 0;
	revDiagonal = 0;
	hasWon = 1;
	winnerPlayer = winner;
	inALine = inaRow;
	nrOfPlays = 0;
}

void GameLogic::UpdateGameState(int i, int j) {
	if (currentPlayer == X) {
		col[i]++;
		row[j]++;
		if (i == j) {
			diagonal++;
		}
		if (i == (matrixSize - 1 - j)) {
			revDiagonal++;
		}
	}
	else {
		col[i]--;
		row[j]--;
		if (i == j) {
			diagonal--;
		}
		if (i == (matrixSize - 1 - j)) {
			revDiagonal--;
		}
	}
}

void GameLogic::CheckWinCondition(int i, int j) {
	if ((col[i] == matrixSize) | (row[j] == matrixSize) | (diagonal == matrixSize) | (revDiagonal == matrixSize)
		| (col[i] == -matrixSize) | (row[j] == -matrixSize) | (diagonal == -matrixSize) | (revDiagonal == -matrixSize)) {
		winnerPlayer->SetType(currentPlayer);
		hasWon = 2;
		return;
	}
	
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			if ((*SymbolMatrix)[i][j].GetType() == EMPTY) {
				return;
			}
		}
	}
	winnerPlayer->SetType(EMPTY);
	hasWon = 2;
}

void GameLogic::ChangePlayer() {
	if (currentPlayer == X) {
		currentPlayer = O;
	}
	else {
		currentPlayer = X;
	}
}

void GameLogic::CheckWinCondition2(int i, int j) {
	int findRowWinner = 0;
	int findColWinner = 0;
	int findDiagWinner = 0;
	int findRevDiagWinner = 0;
	
	for (int x = (1 - *inALine); x < *inALine; x++) {
		if (((j + x) <= matrixSize - 1) && ((j + x) >= 0)) {
			if (((*SymbolMatrix)[i][j + x].GetType() == currentPlayer)) {
				findRowWinner++;
				if (findRowWinner == *inALine) {
					winnerPlayer->SetType(currentPlayer);
					hasWon = 2;
					return;
				}
			}
			else {
				findRowWinner = 0;
			}
		}
		
			if (((i + x) <= matrixSize - 1) && ((i + x) >= 0)) {
				if ((*SymbolMatrix)[i + x][j].GetType() == currentPlayer) {
					findColWinner++;
					if (findColWinner == *inALine) {
						winnerPlayer->SetType(currentPlayer);
						hasWon = 2;
						return;
					}
				}
				else {
					findColWinner = 0;
				}
			}
			if (((i + x) <= matrixSize - 1) && ((i + x) >= 0) && ((j + x) <= matrixSize - 1) && ((j + x) >= 0)) {
				if ((*SymbolMatrix)[i + x][j + x].GetType() == currentPlayer) {
					findDiagWinner++;
					if (findDiagWinner == *inALine) {
						winnerPlayer->SetType(currentPlayer);
						hasWon = 2;
						return;
					}
				}
				else {
					findDiagWinner = 0;
				}
			}
			if (((i - x) >= 0) && ((i - x) <= matrixSize - 1) && ((j + x) <= matrixSize - 1) && ((j + x) >= 0)) {
				if ((*SymbolMatrix)[i - x][j + x].GetType() == currentPlayer) {
					findRevDiagWinner++;
					if (findRevDiagWinner == *inALine) {
						winnerPlayer->SetType(currentPlayer);
						hasWon = 2;
						return;
					}
				}
				else {
					findRevDiagWinner = 0;
				}
			}
		}
	if (nrOfPlays == (matrixSize * matrixSize)) {
		winnerPlayer->SetType(EMPTY);
		hasWon = 2;
	}
	return;
	
}

void GameLogic::ChangeWinner() {
	if (winnerPlayer->GetType() == X) {
		winnerPlayer->SetType(O);
	}
	else if (winnerPlayer->GetType() == O) {
		winnerPlayer->SetType(X);
	}
}

int GameLogic::Update(sf::Vector2i mouseCoordinates) {
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			rectangle = (*SymbolMatrix)[i][j].GetRectangle();
			if (rectangle.contains(mouseCoordinates.x, mouseCoordinates.y)) {
				if ((*SymbolMatrix)[i][j].GetType() == EMPTY) {
					nrOfPlays++;
					ChangeWinner();
					(*SymbolMatrix)[i][j].SetType(currentPlayer);
					CheckWinCondition2(i, j);
					//UpdateGameState(i, j);
					//CheckWinCondition(i, j);
					ChangePlayer();
					return hasWon;
				}
			}
		}
	}
	return 1;
}