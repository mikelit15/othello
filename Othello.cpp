/*
 * Othello
 *
 * Jaydon Reap and Mike Litvin
 */

#include "Othello.hpp"

Othello::Othello() {
	numplayers = 0;
	player1 = Player("comp1", 'O');
	player2 = Player("comp2", 'B');
}

Othello::Othello(string st1, char c) {
	numplayers = 1;
	player1 = Player(st1, c);

	if (c != 'B') {
		player2 = Player();
	} else {
		player2 = Player("comp1", 'O');
	}
}

Othello::Othello(string st1, char c, string st2, char c2) {
	numplayers = 2;
	player1 = Player(st1, c);
	player2 = Player(st2, c2);
}

void Othello::makemat() {
	for (int x = 0; x < boardSize; x++){
		for (int y = 0; y < boardSize; y++) {
			board[x][y] = '-';
		}
	}

	board[3][3] = 'B';
	board[4][4] = 'B';
	board[4][3] = 'O';
	board[3][4] = 'O';
}

void Othello::printmat() {
	cout << "\t";
	for (int i = 0; i < boardSize; i++) {
		cout << "\t" << i;
	}

	cout << endl;

	for (int i = 0; i < boardSize; i++) {
		cout << "\t" << i;
		for(int j = 0; j < boardSize; j++) {
			cout << "\t" << board[j][i];
		}
		cout << endl;
	}
	cout << endl;
}

void Othello::placepiece(Player p) {
	int x = 0;
	int y = 0;

	bool valid = false;
	while (!valid) {
		cout << "Enter x coordinate: ";
		cin >> x;
		cout << "Enter y coordinate: ";
		cin >> y;
		cout << endl;

		valid = isValidPiece(x, y);
	}

	int count = flipPiecesInAllDirections(x, y, p.piece, true);

	if (count > 0) {
		board[x][y] = p.piece;
	} else {
		cout << "Player forfeits turn" << endl;
	}
}

int Othello::flipPiecesInAllDirections(int x, int y, char piece, bool flip) {
	int count = 0;
	int deltaxs[8] = {1, -1, 0, 0, -1, 1, 1, -1};
	int deltays[8] = {0, 0, 1, -1, 1, -1, 1, -1};

	for (int i = 0; i < 8; i++){
		int temp = countandflippieces(x, y, deltaxs[i], deltays[i], piece, false);

		if (temp != 0) {
			count += temp;

			// Flip those pieces
			if (flip) {
				countandflippieces(x, y, deltaxs[i], deltays[i], piece, true);
			}
		}
	}

	return count;
}

bool Othello::isValidPiece(int x, int y) {
	if (board[x][y] != '-') {
		return false;
	}

	if (x > boardSize || x < 0) {
		return false;
	}

	if (y > boardSize || y < 0) {
		return false;
	}

	return true;
}

int Othello::countandflippieces(int x, int y, int deltax, int deltay, char piece, bool flip) {
	int i = x + deltax;
	int j = y + deltay;
	int count = 0;

	while (i < boardSize && i > 0 && j < boardSize && j > 0) {
		char space = board[i][j];

		if (space == '-') {
			return 0;
		}

		if (space == piece) {
			return count;
		}

		if (flip){
			board[i][j] = piece;
		}

		count++;
		i += deltax;
		j += deltay;
	}

	return 0;
}

void Othello::compplacepiece(Player p) {
	// Get a nice seeded rand
	srand(time(NULL));

	int x = 0;
	int y = 0;
	int highest = 0;


	// Loop through every spot on the board
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			int count = flipPiecesInAllDirections(j, i, p.piece, false);

			if (count > highest) {
				highest = count;
				x = j;
				y = i;
			} else if (count == highest) {
				//Randomly pick one of the two positions
				int coin = rand() % 2;

				if (coin > 0) {
					x = j;
					y = i;
				}
				// otherwise we stick with the position we got!
			}
		}
	}

	// Place the piece and flip the board where applicable
	flipPiecesInAllDirections(x, y, p.piece, true);
	board[x][y] = p.piece;
}

void Othello::ckwin() {
	int p1pts = 0;
	int p2pts = 0;

	for(int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++) {
			char space = board[j][i];
			if (player1.piece == space){
				p1pts++;
			} else if (player2.piece == space) {
				p2pts++;
			}
		}
	}

	if (p1pts > p2pts) {
		cout << "Player 1 won with: " << p1pts << " versus " << p2pts << endl;
	} else if (p2pts > p1pts) {
		cout << "Player 2 won with: " << p2pts << " versus " << p1pts << endl;
	} else {
		cout << "It was a draw! Each player had " << p1pts << " points!" << endl;
	}
}

void Othello::playGame(){
    makemat();
    printmat();
    bool play = true;
    int fullsqrs = 0;
    Player p = player1;
    bool whichp = true;
    bool turn = true;

    if (rand()%2 == 0) {  // p1 plays first
    	p = player2;
    	turn = false;
    	whichp = false;
    }


    while ((play) && (fullsqrs < 61)){
    	cout << endl << p.name <<" ("<<p.piece<<") choose your square: "<<endl;
        if ((numplayers == 2) || ((numplayers == 1) && turn)){
            placepiece(p);
        }
        else if ((numplayers == 0) || ((numplayers == 1) && (turn == false))){
            compplacepiece(p);

        }
        turn = !turn;
        printmat();
        if (whichp) {
        	p = player2;
        	whichp = false;
        }
        else {
            p = player1;
            whichp = true;
        }
        fullsqrs+=1;
    }
    ckwin();
}


