#include "BoardB.h"
#include <fstream>
#include <sstream>

/*
Clears screen (alternative to system call).
*/
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
}

/*
Converts letters indicating de position of the first letter of the word to numbers.
*/
unsigned int indexConvert(char letter)
{
  string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  return letters.find(letter) % 26;
}

/*
Draws title.
*/
void drawTitle()
{
  setcolor(9);
  for (int i = 1; i < 121; i += 2)
  {
    setcolor(9);
    cout << char(196);
    setcolor(12);
    cout << char(196);
  }
  setcolor(9);
  gotoxy(53, 1);cout << "BOARD BUILDER" << endl;
  for (int i = 1; i < 121; i += 2)
  {
    setcolor(9);
    cout << char(196);
    setcolor(12);
    cout << char(196);
  }
  setcolor(15);
  cout << endl;
}

/*
Searches for word in a file, returns true if it is in the file and false otherwise.
*/
bool searchWords(const string &word)
{
  string temp; // Auxiliar string to read file lines.
  ifstream fin;
  fin.open("WORDS.txt");
  if (fin.fail()) 
  {
    cout << "Input file opening failed.\n";
    exit(1);
  }
  do { // Check in the WORDS.txt file if there is the word you ara looking for
    temp = "";
    getline(fin, temp);
  } while (temp < word); // The search ends when the word is found or exceeded alphabetically

  if (word == temp) 
    cout << "Word was found!" << endl;
  else
    cout << "Word not found!" << endl;

  fin.close();
  return temp==word;
}

/*
Checks if the word has already been used.
*/
bool alreadyInBoard(const string &word, const vector<string> &wordsUsed)
{
  for (int i = 0; i < wordsUsed.size(); i++)
    if (word == wordsUsed[i]) {
      cerr << "The word is already in board!" << endl;
      return false;
    }
  return true;
}

/*Ask for the board's name (extension .txt is not required).*/
string boardName() {
  string fileName;
  bool validFileName;
  do {
    validFileName = true;
    cout << "Please enter the board's name: ";
    getline(cin, fileName);

    if (cin.eof()) { // Close the program if ctrl+z is pressed.
      cerr << "\n\nThe board was unsuccessfully built.\n\n";
      exit(0);
    }
    if (!fileName.size()) { // Don't allow none name.
      cerr << "The board file must have a name!" << endl;
      validFileName = false;
    }
    else if (fileName.find_first_of("\\/:*?<>|") != std::string::npos) { // Don't allow special characteres.
      cerr << "You can't give that name to a file!" << endl;
      validFileName = false;
    }
  } while (!validFileName);

  return fileName + ".txt";
}

/*
Checks if the height and width inserted by the user are valid.
*/
unsigned setSize() {
  bool validInput;
  unsigned size;
  do {
    validInput = true;
    cin >> size;
    if (cin.eof()) { // Close the program if ctrl+z is pressed.
      cerr << "\n\nThe board was unsuccessfully built.\n\n";
      exit(0);
    }
    if (cin.fail()||cin.peek() != '\n') { // Check bad inputs.
      cin.clear();
      cin.ignore(1000, '\n');
      cerr << "Please insert again a number between 4 and 20: ";
      validInput = false;
    }
    else if (size < 4 || size > 20) { // Restricts the allowed size of the board's edges.
      cerr << "Please insert again a number between 4 and 20: ";
      validInput = false;
    }
  } while (!validInput);
  return size;
}

/*
Checks if the position chosen by the user is valid (syntactically and if it is whithin the board's limits).
*/
void posInput(string& pos, const unsigned& height, const unsigned& width) {
  bool validInput;
  do {
    validInput = true;
    cout << "Enter Position (ex: "; setcolor(9); cout << 'A'; setcolor(12); cout << 'b';setcolor(15); cout << "): ";
    cin >> pos;

    if (cin.eof()) // Ends input if ctrl+z is pressed.
      break;

    if (cin.fail() || cin.peek() != '\n') { // Check bad inputs.
      cin.clear();
      cin.ignore(1000, '\n');
      validInput = false;
    }
    else {
      if (!(isalpha(pos[0]) && isalpha(pos[1])) || pos.length() != 2) // Check if the input has the right format.
        validInput = false;
      // Check if the coordinate chosen is into the board.
      else if (!(indexConvert(pos[0]) >= 0 && indexConvert(pos[0]) < height && indexConvert(pos[1]) >= 0 && indexConvert(pos[1]) < width))
      {
        cout << "Position must be inside the board!" << endl;
        validInput = false;
      }
    }
  } while (!validInput);

  if (!cin.eof()) { // Change input to the format that will be impressed in out file.
    pos[0] = toupper(pos[0]);
    pos[1] = tolower(pos[1]);
  }
}

/*
Checks if the orientation chosen by the user is valid.
*/
void oriInput(char& ori) {
  bool validInput;
  do {
    validInput = true;
    cout << "Enter Orientation (H/V): ";
    cin >> ori;

    if (cin.eof()) { // Don't allow the input ends here to avoid invalid boards.
      cin.clear();
      validInput = false;
      cout << "You can't end the insertion here!" << endl;
      continue;
    }

    if (cin.fail() || cin.peek() != '\n' || !isalpha(ori)) { // Check if it was an alphabetic char input and bad inputs.
      cin.clear();
      cin.ignore(1000, '\n');
      validInput = false;
    }
    else {
      ori = toupper(ori); // Change to capital letter, useful in words input and to be impressed in out file.
      if (!((ori == 'H') || (ori == 'V')))
        validInput = false;
    }
  } while (!validInput);
}

/*
Checks if the word inserted by the user is syntactically valid and if it is too long for the board's dimensions or too small (one letter).
*/
bool wordInput(string& word, const unsigned &height, const unsigned &width, bool &validWord) {
  cout << "Enter Word: ";
  cin >> word;

  if (cin.eof())
    return false;

  if (cin.fail() || cin.peek() != '\n') { // Check bad inputs.
    cin.clear();
    cin.ignore(1000, '\n');
    return false;
  }
  else {
    // First filter of word input. Word can't be just a letter neither bigger than board
    if (word.length() == 1 || (word.length() > height&& word.length() > width)) 
      return false;                                                             
    for (int k = 0; k < word.length(); k++) // Transforms the word in order to be indentified in WORDS.txt file.
      word[k] = tolower(word[k]);

    return true;
  }
}

int main()
{
  char ori;            // inputs by
  string pos, word;    // user 
  vector <string> wordsUsed;
  bool validWord, endOfInsert = false;
  ofstream outputFile;

  drawTitle();
  cout << endl;
  cout << "To stop inserting words use CTRL+Z (in 'Position:')!" << endl << endl;

  outputFile.open(boardName());

  cout << "Please enter the number of board lines: ";
  const unsigned HEIGHT = setSize();
  cout << "Please enter the number of board columns: ";
  const unsigned WIDTH = setSize();

  Board board(HEIGHT, WIDTH);
  outputFile << HEIGHT << 'x' << WIDTH << endl;

  // Start insertion process.
  while (!endOfInsert) // Breaks when cin.eof() == true 
  {
    clrscr();
    drawTitle();
    cout << endl;
    board.showBoard();
    cout << endl;
    do {
      validWord = true;
      posInput(pos, HEIGHT, WIDTH);
      if (cin.eof())     // handles ctrl+Z
        endOfInsert = true;
      else {
        oriInput(ori);

        if (!wordInput(word, HEIGHT, WIDTH, validWord)) { // Make word input and the first filters.
          if (cin.eof()) { // Don't allow the input ends here to avoid invalid boards.
            cin.clear();
            cerr << "You can't end the insertion here!" << endl;
          }
          else
            cerr << "Word or location not valid!" << endl;
          validWord = false;
        }
        // Second filter: check if word was has already been chosen or if not in WORDS.txt file
        else if (!(alreadyInBoard(word, wordsUsed) && searchWords(word))) { 
          validWord = false;
          cerr << "Word is not valid!" << endl;
        }
        // Third filter: check if the words fits in the board and meets restrictions of insertion.
        else if (!board.canBePlaced(word, indexConvert(pos[0]), indexConvert(pos[1]), ori)) {
          validWord = false;
          cerr << "Word and location are incompatible!" << endl;
        }
      }
    } while (!endOfInsert && !validWord);

    if (endOfInsert) // If input is over does nothing but ends the program.
      continue;

    // If arrive here, everything is ok to insert the word in board and in out file.
    
    wordsUsed.push_back(word); // The same word won't be able to be inserted again.

    // Transform word in right format to be written in board and in out file (capital letters).
    for (int k = 0; k < word.length(); k++) 
      word[k] = toupper(word[k]);
    board.writeWord(indexConvert(pos[0]), indexConvert(pos[1]), ori, word); // Write in board.
    
    string str = pos + " " + ori + " " + word; // Write in out file.
    outputFile << str << endl;

    Sleep(1000);
  }

  if (board.numLetters() < 14)
    cout << "\n\nThe board was unsuccessfully built, it's unusable.\n\n";
  else
    cout << "\n\nThe board was successfully built!\n\n";

  outputFile.close();
  return 0;
}