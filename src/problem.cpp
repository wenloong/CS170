#include "../header/problem.h"

using namespace std;

void Problem::printWelcome() {
   int sid = 862154819;

   cout << "Welcome to \"" << sid << "\" 8 puzzle solver." << endl;
}

void Problem::printPuzzle() {
   for (int i = 0; i < puzzle.size(); i++) {
      for (int j = 0; j < puzzle[i].size(); j++) {
         cout << puzzle[i][j] << " ";
      }
      cout << endl;
   }
}

void Problem::puzzleChoiceInput() {
   cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
   cin >> puzzleChoice;
   cout << endl;
}

void Problem::algoChoiceInput() {
   cout << "Enter your choice of algorithm" << endl;
   cout << "1. Uniform Cost Search" << endl;
   cout << "2. A* with the Misplaced Tile Heuristic" << endl;
   cout << "3. A* with the Eucledian distance Heuristic" << endl;
   cin >> algoChoice;
   cout << endl;
}

void Problem::puzzleGenInput() {
   string row;

   cout << "Enter your puzzle, use a zero to represent to blank" << endl;
   cout << "Enter the first row, use space or tabs between numbers ";
   cin.clear();
   cin.ignore(1);
   getline(cin, row);
   cout << endl;
   convert_to_row(row, 1);

   cout << "Enter the second row, use space or tabs between numbers ";
   cin.clear();
   cin.ignore(1);
   getline(cin, row);
   cout << endl;
   convert_to_row(row, 2);

   cout << "Enter the third row, use space or tabs between numbers ";
   cin.clear();
   cin.ignore(1);
   getline(cin, row);
   cout << endl;
   convert_to_row(row, 3);

   convert_to_puzzle(this->topRow, this->midRow, this->botRow);
}

void Problem::convert_to_row(string input, int row) {
   input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
   char col_1 = input[0];
   char col_2 = input[1];
   char col_3 = input[2];

   if (row == 1) {
      topRow.push_back(col_1);
      topRow.push_back(col_2);
      topRow.push_back(col_3);
   } else if (row == 2) {
      midRow.push_back(col_1);
      midRow.push_back(col_2);
      midRow.push_back(col_3);
   } else {
      botRow.push_back(col_1);
      botRow.push_back(col_2);
      botRow.push_back(col_3);
   }
}

void Problem::convert_to_puzzle(vector<char> top, vector<char> mid, vector<char> bot) {
   for (int i = 0; i < ROW_SIZE; i++) {
      for (int j = 0; j < COL_SIZE; j++) {
         this->puzzle[i][j] = top[j];
      }
   } 
}

int Problem::getPuzzleChoice() {
   return puzzleChoice;
}

int Problem::getAlgoChoice() {
   return algoChoice;
}





