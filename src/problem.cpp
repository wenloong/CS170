#include "../header/problem.h"

using namespace std;

void Problem::printWelcome() {
   int sid = 862154819;

   cout << "Welcome to \"" << sid << "\" 8 puzzle solver." << endl;
}

void Problem::puzzleChoiceInput() {
   cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
   cout << "[guestUser@root]$ ";
   cin >> puzzleChoice;
   cout << endl;
}

void Problem::algoChoiceInput() {
   cout << "Enter your choice of algorithm" << endl;
   cout << "1. Uniform Cost Search" << endl;
   cout << "2. A* with the Misplaced Tile Heuristic" << endl;
   cout << "3. A* with the Eucledian distance Heuristic" << endl;
   cout << "[guestUser@root]$ ";
   cin >> algoChoice;
   cout << endl;
}

void Problem::puzzleGenInput() {
   string row;

   cout << "Enter your puzzle, use a zero to represent to blank" << endl;
   cout << "Enter the first row, use space or tabs between numbers ";
   cin.ignore(1);
   getline(cin, row);
   convert_to_row(row, 1);
   row = "";

   cout << "Enter the second row, use space or tabs between numbers ";
   cin.clear();
   getline(cin, row);
   cout << row << endl;
   convert_to_row(row, 2);

   cout << "Enter the third row, use space or tabs between numbers ";
   cin.clear();
   getline(cin, row);
   convert_to_row(row, 3);

   initial_state = new Puzzle(this->topRow, this->midRow, this->botRow);
   //convert_to_puzzle(this->topRow, this->midRow, this->botRow);
}

void Problem::convert_to_row(string input, int row) {
   input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
   char col_1 = input[0];
   char col_2 = input[1];
   char col_3 = input[2];
   cout << "1: " << col_1 << endl;
   cout << "2: " << col_2 << endl;
   cout << "3: " << col_3 << endl;


   if (row == 1) {
      topRow.push_back(col_1);
      topRow.push_back(col_2);
      topRow.push_back(col_3);
      cout << "TOP" << endl;
   } else if (row == 2) {
      midRow.push_back(col_1);
      midRow.push_back(col_2);
      midRow.push_back(col_3);
      cout << "MID" << endl;
   } else {
      botRow.push_back(col_1);
      botRow.push_back(col_2);
      botRow.push_back(col_3);
      cout << "BOT" << endl;
   }
}

//void Problem::convert_to_puzzle(vector<char> top, vector<char> mid, vector<char> bot) {
//   initial_state = new Puzzle(top, mid, bot); 
//}

int Problem::getPuzzleChoice() {
   return puzzleChoice;
}

int Problem::getAlgoChoice() {
   return algoChoice;
}





