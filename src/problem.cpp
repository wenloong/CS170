#include "../header/problem.h"

using namespace std;

void Problem::printWelcome() {
   int sid = 862154819;

   cout << "Welcome to \"" << sid << "\" 8 puzzle solver." << endl;
}

void Problem::printPuzzle() {
   for (int i = 0; i < ROW_SIZE; i++) {
      for (int j = 0; j < COL_SIZE; j++) {
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
   string top, mid, bot;

   cout << "Enter your puzzle, use a zero to represent to blank" << endl;
   cout << "Enter the first row, use space or tabs between numbers ";
   cin >> top;
   cout << endl;

   cout << "Enter the second row, use space or tabs between numbers ";
   cin >> mid;
   cout << endl;

   cout << "Enter the third row, use space or tabs between numbers ";
   cin >> bot;
   cout << endl;

   convert_to_row(top, 1);
   convert_to_row(mid, 2);
   convert_to_row(bot, 3);

   convert_to_puzzle(top, mid, bot);
}

void Problem::convert_to_row(string in, int row) {
   in.erase(remove(in.begin(), in.end(), ' '), in.end());
   char col_1 = in[0];
   char col_2 = in[1];
   char col_3 = in[2];

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

void Problem:convert_to_puzzle(vector<char> top, vector<char> mid, vector<char> bot) {
   for (int i = 0; i < ROW_SIZE; i++) {
      for (int j = 0; j < COL_SIZE; j++) {
         puzzle[i][j] = top[j];
      }
   } 
}

int Problem::getPuzzleChoice() {
   return puzzleChoice;
}

int Problem::getAlgoChoice() {
   return algoChoice;
}





