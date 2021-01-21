#ifndef PLAYER_H
#define PLAYER_H

#include "Pool.h"
#include <string>

class Player {
public:
	Player(Pool& p, const unsigned &i, vector<unsigned>& colorsUsed);
	string getName() const;
	void printName() const;
	unsigned nameSize() const;
	unsigned getColor() const;
	void insertTile(const char &c);
	bool getTile(char c, bool erase);
	void showTiles() const;
	unsigned getChips() const;
	void raiseChips(unsigned newChips, unsigned &totalChips);
	void resetChips();
	vector<char> getAllTiles() const;
private:
	string name;
	vector<char> tiles; // Tiles in player hand.
	unsigned chips; // Player's chips.
	unsigned color;
	void setName(const unsigned& i);
	void setColor(vector<unsigned>& colorsUsed);


};
#endif