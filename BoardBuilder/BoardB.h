#ifndef BOARDB_H
#define BOARDB_H

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Functions used in BoardB.cpp and BoardBuilder.cpp
void setcolor(unsigned int color);
void gotoxy(int x, int y);
//--------------------------------------------------

/*
Each letter (char) is associated to two flags: if v=1, the letter correspond to a vertical word,
else/also if h=1 the letter correspond to a horizontal word.
*/
struct Letter {
  char chr = ' ';
  bool v = 0, h = 0;
};

class Board {
public:
  Board(const unsigned &nLines, const unsigned &nColumns);
  void showBoard() const;
  unsigned numLetters() const;
  void writeWord(unsigned c1, unsigned c2, const char& ori, const string& word);
  bool canBePlaced(string word, int y, int x, char dir) const;

private:
  unsigned height, width;
  vector<vector<Letter>> board;
  string lines, columns;
  bool adjacentWord(string word, const int& y, const int& x, char dir) const;
  bool isValidPosition(int y, int x) const;
  string boardSize(unsigned size, int n) const;
  void fillBoard();
};
#endif
