#pragma once
#include <SFML/Graphics.hpp>
#include "Symbol.h"

class GameLogic {
public:
	GameLogic(std::vector<std::vector < Symbol > >*, Symbol*, int*);
	void CheckWinCondition(int, int);
	void CheckWinCondition2(int, int);
	void ChangePlayer();
	void UpdateGameState(int, int);
	int Update(sf::Vector2i);
	void ChangeWinner();

private:
	int nrOfPlays;
	int matrixSize;
	int hasWon;
	int diagonal;
	int revDiagonal;
	int *inALine;
	std::vector<std::vector < Symbol > > *SymbolMatrix;
	std::vector<int> row;
	std::vector<int> col;
	sf::IntRect rectangle;
	Type currentPlayer;
	Symbol *winnerPlayer;
};