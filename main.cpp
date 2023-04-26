/*
 * Othello
 *
 * Jaydon Reap and Mike Litvin
 */

#include <iostream>
#include <stdlib.h>
#include "Othello.hpp"
#include <time.h>
using namespace std;

int main() {
	srand(time(NULL));
	Othello game("b1",'B',"s1",'O');
	Othello game2("b1",'B');
	Othello game3;
	game2.playGame();
}
