#include "Board.h"
#include "Pool.h"
#include "Player.h"
#include <ctime>
#include <iomanip>
#include <algorithm>

void drawTitle() {
	setcolor(0, 1);
	gotoxy(52, 1); cout << "                 ";
	gotoxy(52, 2); cout << " SCRABBLE JUNIOR ";
	gotoxy(52, 3); cout << "                 ";
	setcolor(15, 0);
	gotoxy(0, 5);
}

/**Clean the screen and then draw the title.*/
void clrscr(void) {
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
	drawTitle();
}

/* Draw the correspondence of colors to numbers */
void drawColorsChoice() {
	vector<string> colors = { "Blue", "Green", "Cyan", "Red", "Mangenta", "Brown", "Light Gray", "Dark Gray",
		"Light Blue", "Light Green", "Light Cyan", "Light Red", "Light Mangenta", "Yellow", "White" };
	gotoxy(75, 5);
	cout << "Colors code:";
	for (int i = 1; i <= 15; i++) {
		gotoxy(75, i + 6);
		cout << setw(2) << i << "  ->  " << colors[i - 1];
	}
	gotoxy(0, 5);
}

/*Set the number of players.*/
unsigned numberOfPlayers() {
	unsigned n_players;
	do {
		cout << "Number of players (2-4): ";
		cin >> n_players;
		
		if (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			n_players = 0; // Eliminate value of n_players.
		}
		
		cin.ignore(1000, '\n');
	} while (n_players < 2 || n_players > 4);
	return n_players;
	clrscr();
}

/*Set a vector with the coordinates where players will be drawn according with the size of the board and the number of players.*/
void playersLocation(const Board& board, vector<Coor>& playerLocal, const unsigned& N_PLAYERS) {
	Coor location;
	for (unsigned i = 0; i < N_PLAYERS; i++) {
		location.x = 32 - 3 * board.retSize(1) / 2 * (int)pow(-1, i) + 33 * (i % 2);
		location.y = 3 + (4 + board.retSize(0)) * (i / 2) + (int)pow(-1, i / 2) * ((int)board.retSize(0) + 3) / 3;
		playerLocal.push_back(location);
	}
}

/*Display the game board, including ponctuations and others*/
void gameBoard(const vector<Coor>& playerLocal, const Board& board, const vector<Player>& player, const Pool& pool, const unsigned& N_PLAYERS) {
	clrscr();
	drawTitle();
	board.showBoard(); // Show board
	cout << endl;
	// Show players chips and their tiles
	for (unsigned i = 0; i < N_PLAYERS; i++) {
		gotoxy(playerLocal[i].x, playerLocal[i].y);
		player[i].printName();
		gotoxy(playerLocal[i].x, playerLocal[i].y + 1);
		cout << "Chips: " << player[i].getChips();
		gotoxy(playerLocal[i].x, playerLocal[i].y + 2);
		cout << "Tiles: ";
		player[i].showTiles();
	}
	gotoxy(65 + 3 * board.retSize(1) / 2, 4);
	cout << "Tiles in pool: " << pool.retTiles();
	gotoxy(0, 9 + board.retSize(0));
}

/*Ask player for coordinates to make a move and make it.
secondTile variable: 0 correspond to the first move of the turn, 1 correspond to the second move of the turn.*/
void move(bool secondTile, unsigned &totalChips, Player &player, Board& board, Pool& pool) {
	Coor play; // Coordinates in numbers.
	string position;// Coordinates in letters.
	char c; // Auxiliar char.
	bool validMove;
	unsigned chipsToRaise=0; 
	do {
		validMove = true;
		player.printName(); cout << ": ";
		cin >> position; // Read alphabetic coordinates

		if (cin.eof())  // Check if someone finished the game out of time and don't do anything else is this case.
			continue;

		// Check if were introduced a capital letter folowed by a lower case, otherwise ask again.
		if (cin.fail() || cin.peek() != '\n' || position.length() != 2 
			|| !(isupper(position[0]) && islower(position[1]))) 
		{ 
			cin.clear();
			cin.ignore(1000, '\n');
			validMove = false;
			cerr << "Introduce coordinates in right format (ex. Aa)" << endl;
			continue;
		}
		// If it was a valid input (2 chars) and no one gave up.
		play.y = position[0] - 'A'; // Change alphabetic to number coordinates.
		play.x = position[1] - 'a';
		if (play.y < board.retSize(0) && play.x < board.retSize(1)) { // Check if coordinate is the board.
			c = board.getTile(play); // Set with the letter that is in board on coordinates chosen.
			if (c == ' ') { // Fail input if it is a empty coordinate.
				cerr << "That move is not valid" << endl;
				validMove = false;
			}
			else if (!player.getTile(c, 0)) { // Error message if player don't have the tile in hand.
				cerr << "You don't have that tile" << endl;
				validMove = false;
			}
			else if (!board.validMove(play, chipsToRaise)) { // Error message if coordinates don't correspond to a valid move into the board.
				cerr << "That move is not valid" << endl;      // and at the same time if true begin the move.
				validMove = false;
			}
			else {
				player.getTile(c, 1); // Erase the tile choice from player's hand.
				player.raiseChips(chipsToRaise, totalChips); // Raise player chips and total chips.
				if (secondTile) { // Ignore if is first tile choice.
					for (int _ = 0; _ < 2; _++) {
						if (pool.retTiles() > 0) { // While there are tiles in pool, refill player tiles until max 2.
							c = pool.getTile();
							player.insertTile(c);
						}
						else
							break;
					}
				}
			}
		}
		else {
			validMove = false;
			cerr << "That coordinate is not in the board" << endl;
		}
	} while (!validMove);
}

/* Ask player for the letter he wants to swap and swap with one from the pool.*/
void swap(Player &player, Pool &pool) {
	char auxiliarChar1, auxiliarChar2;
	bool validSwap;
	
	do {
		player.printName(); cout << ", choose a tile to swap: ";
		cin >> auxiliarChar1;

		if (cin.eof())
			break;
		if (cin.fail() || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(1000, '\n');
			validSwap = false;
			cerr << "Input invalid" << endl;
		}

		else {
			validSwap = player.getTile(auxiliarChar1, 1); // If the player has the auxiliarChar1 in hand erase it and go on.
			if (!validSwap)
				cerr << "You don't have that tile" << endl;
		}
	} while (!validSwap);

	if (!cin.eof()) {
		auxiliarChar2 = pool.getTile(); // Get a tile from pool.
		pool.insertTile(auxiliarChar1); // Insert tile chosen in pool.
		player.insertTile(auxiliarChar2); // Put tile chosen in player's hand.
	}
}

/*Check if any of player tiles is coincident with any board's avaiable moves.*/
bool checkValidMoves(vector<char> playerTiles, const Board &board) {
	for (unsigned i = 0; i < playerTiles.size(); i++)
		if (board.checkValidMove(playerTiles[i])) // Method of board to check if a letter is a valid move.
			return true;
	return false;
}

/*Announce the winner or the tie.*/
void announceWinner(vector<Player>& player) {
	unsigned max = 0, chips, winnerPlayer;
	bool draw=true;
	
	sort(player.begin(), player.end(), [](const Player& lhs, const Player& rhs) {
		return lhs.getChips() > rhs.getChips();
	}); // Sort the players by their chips.
	
	Sleep(2000);
	clrscr();

	// Draw classification table. -------------------------------|
	gotoxy(43, 11); cout << char(218); 
	for (int _ = 0;_ < 24;_++) cout << char(196);
	cout << char(194);
	for (int _ = 0;_ < 7;_++) cout << char(196);
	cout << char(191);
	
	gotoxy(43, 12); cout << char(179) << " Players";
	gotoxy(68, 12); cout << char(179) << " Chips " << char(179);
	
	gotoxy(43, 13); cout << char(195);
	for (int _ = 0;_ < 24;_++) cout << char(196);
	cout << char(197);
	for (int _ = 0;_ < 7;_++) cout << char(196);
	cout << char(180);

	gotoxy(43, 14+player.size()); cout << char(192);
	for (int _ = 0;_ < 24;_++) cout << char(196);
	cout << char(193);
	for (int _ = 0;_ < 7;_++) cout << char(196);
	cout << char(217);
	// -----------------------------------------------------------|
	// Draw the players names and chips in the classification table.
	for (unsigned i = 0; i < player.size();i++) {
		chips = player[i].getChips();
		gotoxy(43, 14 + i); cout << char(179) << " "; player[i].printName();
		gotoxy(68, 14 + i); cout << char(179) << " " << setw(3) << chips << "   " << char(179);
		
		if (chips > max) { // Check if there is a winner
			winnerPlayer = i;
			draw = false;
			max = chips;
		}
		else if (chips == max)
			draw = true;
	}
	// -----------------------------------------------------------|
	if (draw) { // Annouce a draw
		gotoxy(56, 6); cout << "########";
		gotoxy(56, 7); cout << "# DRAW #";
		gotoxy(56, 8); cout << "########";
	}
	else { // Announce the winner
		int x = 60 - (player[winnerPlayer].nameSize() + 8) / 2;
		gotoxy(x, 6); for (unsigned _ = 0; _ < player[winnerPlayer].nameSize() + 8; _++) cout << "#";
		gotoxy(x, 7); cout << "#"; gotoxy(x + player[winnerPlayer].nameSize() + 7, 7); cout << "#";
		gotoxy(x, 8); for (unsigned _ = 0; _ < player[winnerPlayer].nameSize() + 8; _++) cout << "#";
		// Color show.
		for (int color = 1; color <= 15;color++) {
			setcolor(color);
			gotoxy(x + 2, 7);
			cout << player[winnerPlayer].getName() << " WON";
			gotoxy(0, 0); // 
			Sleep(300);
		}
		setcolor(player[winnerPlayer].getColor()); // Ends show with player's color
		gotoxy(x + 2, 7);
		cout << player[winnerPlayer].getName() << " WON";
		setcolor(15);
	}
	gotoxy(0, 20);
}


int main() {
	unsigned turn = 0; // Indicates the player that must play.
	unsigned totalChips = 0; // Count the chips already earn by all players.
	vector<Player> player; // Vector with the players objects.
	vector<Coor> playerLocal; // Vector with the coordinates where each player will be drawn.
	vector<unsigned> colorsUsed;
	bool endOfGame = false;
	char auxiliarChar; // Auxiliar char.

	srand((unsigned)time(NULL)); // Used to take tiles from the pool by player.

	drawTitle();
	Board board;
	Pool pool(board.retBoard());

	const unsigned TOTAL_WORDS = board.getAllMoves(); // Define the total numbers of words in the board.
	clrscr();

	const unsigned N_PLAYERS = numberOfPlayers(); // Define the number of players.
	if (pool.retTiles() < 7 * N_PLAYERS) { // Stop the program if the number of players isn't enough for the board chosen.
		clrscr();
		cerr << "\nThe board and the number of players chosen are incompatible, please try others\n";
		exit(1);
	}

	clrscr();
	drawColorsChoice();
	for (unsigned i = 0; i < N_PLAYERS; i++) { // Initialize vector with players
		player.push_back(Player(pool, i, colorsUsed));
		cout << endl;
	}
	playersLocation(board, playerLocal, N_PLAYERS); // Define where will be drawn the players.

	while (!endOfGame) { // Start the game.
		turn = turn % N_PLAYERS;

		gameBoard(playerLocal, board, player, pool, N_PLAYERS);

		if (checkValidMoves(player[turn].getAllTiles(), board)) {
			move(0, totalChips, player[turn], board, pool);

			gameBoard(playerLocal, board, player, pool, N_PLAYERS);

			if (totalChips == TOTAL_WORDS || cin.eof()) { // Check if the game is over and if true does
				endOfGame = true;														//  nothing else but finish the game.
				continue;
			}

			if (checkValidMoves(player[turn].getAllTiles(), board)) { // Decide if there will be a second move in this turn.
				move(1, totalChips, player[turn], board, pool);
			}
			else { // See the reason why is not possible to make the second move.
				if (player[turn].getAllTiles().size() == 0) {
					player[turn].printName();cout << " doesn't have more tiles" << endl;
				}
				else {
					player[turn].printName();cout << " doesn't have more match tiles" << endl;
					if (pool.retTiles() > 0) { // Replace the missing tiles in player's hand if possible.
						auxiliarChar = pool.getTile();
						player[turn].insertTile(auxiliarChar);
					}
				}
				Sleep(3000);
			}
		}
		else {
			for (int _ = 0; _ < 2; _++) {
				if (pool.retTiles() > 0) { // If there are tiles in pool allow swap until the maximum of 2 tiles.
					swap(player[turn], pool);

					if (cin.eof()) // If true does nothing else but finish the game.
						break;

					gameBoard(playerLocal, board, player, pool, N_PLAYERS);
				}
				else {
					player[turn].printName(); cout << " doesn't have match tiles and the pool is empty, can't swap any more, must pass" << endl;
					Sleep(3000);
					break;
				}
			}
		}

		if (totalChips == TOTAL_WORDS || cin.eof()) { // Check if the game is over and if true does
			endOfGame = true;                          //  nothing else but finish the game.
			continue;
		}

		turn++; // Change player.
	}

	if (cin.eof()) // If a player give up, take all his chips.
		player[turn].resetChips();

	gameBoard(playerLocal, board, player, pool, N_PLAYERS);
	announceWinner(player);

	return 0;
}