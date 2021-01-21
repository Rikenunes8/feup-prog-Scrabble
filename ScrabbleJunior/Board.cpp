#include "Board.h"
#include <fstream>
#include <string>
#include <sstream>

void setcolor(unsigned int color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
void setcolor(unsigned int color, unsigned int background_color) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == 0)
		SetConsoleTextAttribute(hCon, color);
	else SetConsoleTextAttribute(hCon, color 
		| BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); // White background.
}

/*Change coordinates to print.*/
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// PUBLIC 

Board::Board() {
	bool open;
	char junk;
	string stri, s;
	ifstream inStream;
	do { // Ask for board until it exists.
		open = true;
		cout << "Choose a path to your board: ";
		getline(cin, s);

		if (cin.eof())
			exit(1);

		if (s.find(".txt", s.size() - 4) == string::npos) { // Force the file to be a text file.
			cerr << "The file must be a text file in .txt format\n";
			open = false;
		}
		else {
			inStream.open(s);
			if (!inStream.is_open()) {
				cerr << "Not correct repository\n";
				open = false;
			}
		}
	} while (!open);
	
	// Read from the file the dimensions of the board.
	inStream >> height;
	inStream >> junk;
	inStream >> width; inStream.ignore(1000, '\n');
	
	lines = boardSize(height, 65); // Set the vertical edge of board.
	columns = boardSize(width, 97); // Set the horizontal edge of board.
	fillBoard();
	while (getline(inStream, stri) && stri != "") // Read each line of the file (after dimensions) until it ends or find a empty line.
		sstream(stri);
	inStream.close();
}

/*Cheks if the position given is in the possibleMoves vector and return true by "possible" variable if it is. 
Also turn the flag in that position of the board true (used), update the possibleMoves
vector to the next position of the word/words and count how many words have finished, increasing the variable
"chipaToRaise" given by referenced to then raise the player pontuaction.*/
bool Board::validMove(const Coor &c, unsigned &chipsToRaise) {
	bool possible = false;
	for (unsigned i = 0; i < possibleMoves.size();i++) {
		if (c.y == possibleMoves[i].y && c.x == possibleMoves[i].x) {
			possible = true;
			board[c.y][c.x].used = 1;
			do {
				possibleMoves[i].lettersLeft -= 1;
				if (possibleMoves[i].lettersLeft == 0) {
					chipsToRaise += 1; // If the word ends raise chips count 
					break;            // and ends the loop.
				}
				else {
					if (possibleMoves[i].ori == 'H')
						possibleMoves[i].x += 1;
					else if (possibleMoves[i].ori == 'V')
						possibleMoves[i].y += 1;
				}
			} while (board[possibleMoves[i].y][possibleMoves[i].x].used == 1);
		} // Move one position forward until it's not used or the word ends.
	}
	return possible;
}

/*Check if a letter is a possible move*/
bool Board::checkValidMove(char chr) const {
	for (unsigned i = 0; i < possibleMoves.size(); i++)
		if (possibleMoves[i].lettersLeft != 0 && board[possibleMoves[i].y][possibleMoves[i].x].chr == chr)
			return true;
	return false;
}


void Board::showBoard()const {
	// Draw frame's top
	gotoxy(60-3*width/2, 5);
	for (unsigned i = 0;i < width;i++) cout << " " << columns[i] << " ";
	gotoxy(59-3*width/2, 6);
	cout << char(218);
	for (unsigned i = 0;i < width;i++) cout << char(196) << char(196) << char(196);
	cout << char(191);

	// Draw vertical edges and the inside of the board
	unsigned i;
	for (i = 0; i < height; i++) {
		gotoxy(55-3*width/2, 7+i);
		cout << " " << lines[i] << "  " << char(179);
		for (unsigned j = 0;j < width;j++) {
			if (board[i][j].used) {
				setcolor(4);
				cout << " " << board[i][j].chr << " ";
				setcolor(15);
			}
			else
				cout << " " << board[i][j].chr << " ";
		}
		cout << char(179);
	}

	// Draw frame's bottom
	gotoxy(59-3*width/2, i+7);
	cout << char(192);
	for (unsigned i = 0;i < width;i++) cout << char(196) << char(196) << char(196);
	cout << char(217) << endl;
}

/* Returns the char that is in the given position. */
char Board::getTile(const Coor &c) const {
	return board[c.y][c.x].chr;
}
/*Returns the size of the board (number of lines or number of columns.*/
unsigned Board::retSize(bool heightVSwidth) const {
	if (!heightVSwidth)
		return height;
	else
		return width;
}

vector<vector<Letter>> Board::retBoard() const {
	return board;
}

/* Returns the number of all the chars that correspond to a valid move. */
unsigned Board::getAllMoves() const {
	return possibleMoves.size();
}


// PRIVATE

/* Given a size and the initializing char (n=65 -> 'A', n=97 -> 'a') 
returns a string with the next chars until the size (ex. size=3, n=65 returns "ABC"). */
string Board::boardSize(unsigned size, int n) {
	string s="";
	for (unsigned i = 0; i < size;i++)
		s += char(n + i);
	return s;
}

/* Write the word in the board according to orientation and initial position. */
void Board::writeWord(unsigned c1, unsigned c2, char ori, string word) {
	if (ori == 'V')
		for (unsigned i = 0; i < word.length();i++)
			board[c1 + i][c2].chr = word[i];
	else if (ori == 'H')
		for (unsigned i = 0; i < word.length();i++)
			board[c1][c2 + i].chr = word[i];
}

/* Get a word and respective components from a line of the file, increase the
possibleMoves vector and invoke writeWord method. */
void Board::sstream(const string &stri) {
	Moves c; // Check struct comments in Board.h.
	char c1, c2; // Auxiliar chars.
	string word; // Auxiliar string.
	istringstream ss(stri); 
	ss >> c1;
	ss >> c2;
	ss >> c.ori;
	ss >> word;
	c.y = c1 - 'A';
	c.x = c2 - 'a';
	c.lettersLeft = word.length();
	possibleMoves.push_back(c);
	writeWord(lines.find(c1), columns.find(c2), c.ori, word);
}

/* Fill the board with ' ' char and the respective flag = false that indicates 
the coordinate wasn't chosen by any player. This method is used only on Board constructor. */
void Board::fillBoard() {
	Letter l;
	l.chr = ' ';
	l.used = 0;
	//board.resize(height, vector<Letter>(width, l))
	vector<vector<Letter>> v(height, vector<Letter>(width, l));
	board = v;
}

