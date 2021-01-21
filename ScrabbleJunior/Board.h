#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

// This 3 functions are also used in Scrabble.cpp,
void setcolor(unsigned int color);
void gotoxy(int x, int y);
void setcolor(unsigned int color, unsigned int background_color);


/* An element of the board that contains the char and a respective flag that
indicates if that char has already been chosen by a player. */
struct Letter {
	char chr;
	bool used;
};
/*An element of the vector of possible moves that indicates the coordinates avaiablele
as the letter they represent, the orientation of the word that correspond the letter 
in the coordinates and a counter to know when the word is finished. */
struct Moves {
	char ori, chr;
	unsigned y, x, lettersLeft;
};

struct Coor { // Coordinates
	unsigned y, x;
};

class Board {
public:
	Board();
	bool validMove(const Coor &c, unsigned &chipsToRaise);
	bool checkValidMove(char chr) const;
	void showBoard() const;
	char getTile(const Coor &c) const;
	unsigned retSize(bool heightVSwidth) const;
	vector<vector<Letter>> retBoard() const;
	unsigned getAllMoves() const;
private:
	unsigned height, width; // Number of lines and Number of columns of the board.
	vector<vector<Letter>> board;
	vector<Moves> possibleMoves; // All possible moves avaiable in board. One for each word in board.
	string lines, columns; // Ex: 3x2 -> lines = "ABC" and columns = "ab"
	string boardSize(unsigned size, int n);
	void writeWord(unsigned c1, unsigned c2, char ori, string word);
	void sstream(const string &stri);
	void fillBoard();
};

#endif
