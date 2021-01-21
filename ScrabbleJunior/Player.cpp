#include "Player.h"


// PUBLIC

Player::Player(Pool& p, const unsigned &i, vector<unsigned>& colorsUsed) {
	char c;
	for (int i = 0; i < 7;i++) { // Get 7 tiles from pool to the hand of player.
		c = p.getTile();
		insertTile(c);
	}
	chips = 0;
	setName(i);
	setColor(colorsUsed);
}

string Player::getName() const {
	return name;
}

/* Print player's name with the respective color.*/
void Player::printName() const{ 
	setcolor(color);
	cout << name;
	setcolor(15);
}

unsigned Player::nameSize() const {
	return name.length();
}

unsigned Player::getColor() const { 
	return color;
}

void Player::insertTile(const char &c) {
	tiles.push_back(c);
}

/*Return true if the given letter is the player hand and false otherwise.
Also remove the tile from player's hand if erase = true.*/
bool Player::getTile(char c, bool erase) {
	for (unsigned i = 0;i < tiles.size();i++)
		if (c == tiles[i]) {
			if (erase)
				tiles.erase(tiles.begin() + i);
			return true;
		}
	return false;
}

/*Print all the tiles in player's hand.*/
void Player::showTiles() const{
	if (tiles.size() == 0)
		cout << "No more tiles";
	else
		for (unsigned i = 0; i < tiles.size();i++)
			cout << tiles[i] << ' ';
	cout << endl;
}

unsigned Player::getChips() const{
	return chips;
}

/*Raise the chips of the player and the general count of chips.*/
void Player::raiseChips(unsigned newChips, unsigned& totalChips) {
	chips += newChips;
	totalChips += newChips;
}

void Player::resetChips() {
	chips = 0;
}

vector<char> Player::getAllTiles() const{
	return tiles;
}


// PRIVATE

/*Ask for and set player's name.*/
void Player::setName(const unsigned& i) {
	string s;
	do {
		cout << "Player" << i + 1 << "'s name: ";
		getline(cin, s);
		if (s.length() > 20)
			cerr << "The name must have less than 21 characters\n";
	} while (s.length() == 0 || s.length() > 20); // Name must have less than 20 characters.
	name = s;
}

/*Ask for and set player's color.*/
void Player::setColor(vector<unsigned>& colorsUsed) {
	unsigned color;
	bool validColor;
	do {
		validColor = true;
		cout << name << "'s color (1-15): ";
		cin >> color;
		if (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			validColor = false;
			cerr << "Invalid Color" << endl;
		}
		else if (color > 15 || color == 0) {
			validColor = false;
			cerr << "Invalid Color" << endl;
		}
		else {
			for (unsigned i = 0; i < colorsUsed.size(); i++) // Travels the colors used to check if the color has already been used.
				if (color == colorsUsed[i]) {
					validColor = false;
					cerr << "That color has already been chosen" << endl;
					break;
				}
		}
		cin.ignore(1000, '\n');
	} while (!validColor);
	colorsUsed.push_back(color); // Add color chosen to colors used.
	this->color = color;
}
