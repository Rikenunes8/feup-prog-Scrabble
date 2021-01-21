#include "Pool.h"

/* Travels the board and put in the pool all the letters. */
Pool::Pool(const vector<vector<Letter>> &v) {
	unsigned height = v.size();
	unsigned width = v[0].size();
	for (unsigned i = 0; i < height;i++) { 
		for (unsigned j = 0; j < width; j++) {
			if (v[i][j].chr != ' ')
				pool.push_back(v[i][j].chr);
		}
	}
	nTiles = pool.size();
}

/* Insert a letter in the pool and update the number of tiles in the pool. */
void Pool::insertTile(const char &c) {
	pool.push_back(c);
	nTiles++;
}

/* Randomly get a letter from pool and eliminate it from there.
Finnaly update the number of tiles in the pool. */
char Pool::getTile() {
	unsigned n = rand() % pool.size();
	char c = pool[n];
	pool.erase(pool.begin() + n);
	nTiles--;
	return c;
}

/* Return the number of tiles in the pool. */
unsigned Pool::retTiles() const {
	return nTiles;
}