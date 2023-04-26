#include <iostream>
#include <stdlib.h>
/*
 * Othello
 *
 * Jaydon Reap and Mike Litvin
 */

#include <time.h>
#include "Player.hpp"

using namespace std;

class Othello {
public:
	char board[8][8];
	int boardSize = 8;

	Player player1;
	Player player2;
	int numplayers;

	Othello();
	Othello(string s1, char c);
	Othello(string st1, char c, string str2, char c2);

	void makemat();
	void printmat();
	void placepiece(Player p);
	int countandflippieces(int x, int y, int deltax, int deltay, char piece, bool flip);
	void compplacepiece(Player p);
	void ckwin();
	void playGame();

	// Utility methods
	bool isValidPiece(int x, int y);
	int flipPiecesInAllDirections(int x, int y, char piece, bool flip);
};
