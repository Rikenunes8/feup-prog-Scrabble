#include "BoardB.h"

/*
Alows changing the color of the text.
*/
void setcolor(unsigned int color) {
  HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hcon, color);
}

/*
Sets cursor to the position on de console with cordinates (x,y).
*/
void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



/*
Board constructor.
*/
Board::Board(const unsigned &nLines, const unsigned &nColumns) {
  height = nLines; // number of lines
  width = nColumns; // number of columns
  fillBoard();
  lines = boardSize(nLines, 65); // string with alphabetic number of lines
  columns = boardSize(nColumns, 97); // string with alphabetic number of columns
}

/*
Displays board in console.
*/
void Board::showBoard() const {
  // Draw frame's top
  gotoxy(60 - 3 * width / 2, 5);
  for (unsigned i = 0; i < width; i++)
  {
    setcolor(12);
    cout << " " << columns[i] << " ";
  }
  setcolor(15);
  gotoxy(59 - 3 * width / 2, 6);
  cout << char(218);
  for (unsigned i = 0; i < width; i++) cout << char(196) << char(196) << char(196);
  cout << char(191);
  // Draw vertical edges and the inside of the board
  unsigned i;
  for (i = 0; i < height; i++) {
    gotoxy(55 - 3 * width / 2, 7 + i);
    setcolor(9);
    cout << " " << lines[i] << "  ";
    setcolor(15);
    cout << char(179);
    for (unsigned j = 0; j < width; j++) {
      cout << " " << board[i][j].chr << " ";
    }
    cout << char(179);
  }
  // Draw frame's bottom
  gotoxy(59 - 3 * width / 2, i + 7);
  cout << char(192);
  for (unsigned i = 0; i < width; i++) cout << char(196) << char(196) << char(196);
  cout << char(217) << endl;
}

/* Return the number of letters placed in board.*/
unsigned Board::numLetters() const{
  unsigned nLetters = 0;
  for (int y = 0; y < height; y++)
    for (int x = 0; x < width;x++)
      if (board[y][x].chr != ' ')
        nLetters++;
  return nLetters;
}

/*
Places word is 2d matrix board and set the respectve letter's orientation flags.
*/
void Board::writeWord(unsigned c1, unsigned c2, const char& ori, const string& word) {
  if (ori == 'V')
    for (int i = 0; i < word.length(); i++) {
      board[c1 + i][c2].chr = word[i];
      board[c1 + i][c2].v = 1;
    }
  else if (ori == 'H')
    for (int i = 0; i < word.length(); i++) {
      board[c1][c2 + i].chr = word[i];
      board[c1][c2 + i].h = 1;
    }
}

/*
Checks if the word can be placed in the position chosen by the user.
*/
bool Board::canBePlaced(string word, int y, int x, char dir) const
{ // Verify if the word fits in the board.
  if (dir == 'H' && isValidPosition(y, x) && isValidPosition(y, x + word.length() - 1)) {
    for (int i = 0; i < word.length(); i++) {
      // Verify if any letter of word doesn't match with the char in board's same coordinates  or 
      //otherwise if the letter that match is in the same orientation.
      if (!(board[y][x + i].chr == toupper(word[i]) || board[y][x + i].chr == ' ') || board[y][x + i].h)
        return false;
    }
    if (!adjacentWord(word, y, x, dir)) { // Check if although not coincident, the position is invalid for being adjacent.
      cout << "The word is adjacent to an existing word!" << endl;
      return false;
    }
    else
      return true;
  }
  else if (dir == 'V' && isValidPosition(y, x) && isValidPosition(y + word.length() - 1, x)) // Same indications as dir == 'H'
  {
    for (int i = 0; i < word.length(); i++) {
      if (!(board[y + i][x].chr == toupper(word[i]) || board[y + i][x].chr == ' ') || board[y + i][x].v)
        return false;
    }
    if (!adjacentWord(word, y, x, dir)) {
      cout << "The word is adjacent to an existing word!" << endl;
      return false;
    }
    else
      return true;
  }
  return false;
}

/*
Checks if there are any adjacent words to the word chosen by the user, if there are, the placement chosen is
not valid, so it returns false returning true otherwise. Works as a complementary fuction of canBePlaced() function.
*/
bool Board::adjacentWord(string word, const int& y, const int& x, char dir) const {
  int aux = word.length() - 1;

  if (dir == 'H') {
    // If the tips of the word aren't in board's vertical margins and the position behind and forward aren't empty return false.
    if (x != 0)
      if (board[y][x - 1].chr != ' ')
        return false;
    if (x + aux != width - 1)
      if (board[y][x + aux + 1].chr != ' ')
        return false;

    // If not valid adjacent letters under and over word's tips return false.
    for (int i = 0; i < 2; i++) {
      if (y != height - 1) // If word is the bottom of board don't check down.
        if ((board[y + 1][x + aux * i].h && !board[y + 1][x + aux * i].v)
          || (board[y + 1][x + aux * i].v && !board[y][x + aux * i].v))
          return false;
      if (y != 0) // If word is the top of board don't check up.
        if ((board[y - 1][x + aux * i].h && !board[y - 1][x + aux * i].v)
          || (board[y - 1][x + aux * i].v && !board[y][x + aux * i].v))
          return false;
    }

    // If any letter in the middle of word as an adjacent letter that belongs to a
    // word with the same orientation or that is a tip of another word return false.
    for (int i = 1; i < aux; i++) {
      if (y != height - 1) // If word is the bottom of board don't check down.
        if (board[y + 1][x + i].h || (board[y + 1][x + i].v && !board[y][x + i].v))
          return false;
      if (y != 0) // If word is the top of board don't check up.
        if (board[y - 1][x + i].h || (board[y - 1][x + i].v && !board[y][x + i].v))
          return false;
    }

  }
  else if (dir == 'V') { // Same indications as dir == 'H' with the necessary changes.
    if (y != 0)
      if (board[y - 1][x].chr != ' ')
        return false;
    if (y + aux != height - 1)
      if (board[y + aux + 1][x].chr != ' ')
        return false;

    for (int i = 0; i < 2; i++) {
      if (x != width - 1)
        if ((board[y + aux * i][x + 1].v && !board[y + aux * i][x + 1].h)
          || (board[y + aux * i][x + 1].h && !board[y + aux * i][x].h))
          return false;
      if (x != 0)
        if ((board[y + aux * i][x - 1].v && !board[y + aux * i][x - 1].h)
          || (board[y + aux * i][x - 1].h && !board[y + aux * i][x].h))
          return false;
    }

    for (int i = 1; i < aux; i++) {
      if (x != width - 1)
        if (board[y + i][x + 1].v || (board[y + i][x + 1].h && !board[y + i][x].h))
          return false;
      if (x != 0)
        if (board[y + i][x - 1].v || (board[y + i][x - 1].h && !board[y + i][x].h))
          return false;
    }
  }
  return true;
}

/*
Checks if a position is into the board.
*/
bool Board::isValidPosition(int y, int x) const
{
  return (y >= 0 && x >= 0 && y < height && x < width);
}


/*
Returns a string with board size in letters, starting by char of ascii code n.
*/
string Board::boardSize(unsigned size, int n) const {
  string s = "";
  for (int i = 0; i < size; i++)
    s += char(n + i);
  return s;
}

/*
Fills board with blank spaces (' ') and all flags as false.
*/
void Board::fillBoard() {
  Letter l;
  vector<vector<Letter>> v(height, vector<Letter>(width, l));
  board = v;
}
