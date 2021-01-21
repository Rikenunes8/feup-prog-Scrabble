#ifndef POOL_H
#define POOL_H

#include "Board.h"

class Pool {
public:
	Pool(const vector<vector<Letter>> &v);
	void insertTile(const char &c);
	char getTile();
	unsigned retTiles() const;
private:
	unsigned nTiles; // Number of tiles in the pool.
	vector<char> pool; // All the tiles that are in the pool.
};
#endif