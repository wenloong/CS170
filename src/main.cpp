#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void printWelcome();
void printPuzzleQ(int row);
string getAlgoChoice();

int main() {
   int puzzleChoice = 0;
   string userInput;
   int userRowInput;
   vector<char> row;
   vector<vector<char>> puzzle{ { '0', '1', '2'},
                                { '4', '8', 'b'},
                                { '7', '6', '5'} };

   printWelcome();
   cin >> puzzleChoice;
   cout << endl;

   if (puzzleChoice == 2) {
      for (int i = 0; i < puzzle.size(); i++) {
         row.clear();
         printPuzzleQ(i);
         cin >> userInput;
         cout << endl;
         userRowInput = stoi(userInput);
         cout << userRowInput << endl;
 
         while (userRowInput > 0) {
            int digit = userRowInput % 10;
            userRowInput /= 10;
            row.push_back((char)digit);
         }

         for (int j = 0; j < puzzle[i].size(); j++) {
            puzzle[i][j] = row[j];            
         }
      }
   }

   for (int i = 0; i < puzzle.size(); i++) {
      for (int j = 0; j < puzzle[i].size(); j++) {
         cout << puzzle[i][j] << " ";
      }
      cout << endl;
   }
}

void printWelcome() {
   int sid = 862154819;

   cout << "Welcome to \"" << sid << "\" 8 puzzle solver." << endl;
   cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
}

void printPuzzleQ(int row) {
   if (row == 0) {
      cout << "Enter your puzzle, use a zero to represent the blank" << endl;
      cout << "Enter the first row, use space or tabs between numbers ";
   } else if (row == 1) {
      cout << "Enter the second row, use space or tabs between numbers ";
   } else if (row == 2) {
      cout << "Enter the third row, use space or tabs between numbers ";
   }
}

string getAlgoChoice() {
   vector<string> algorithms{"Uniform Cost Search", "A* with the Misplaced Tile Heuristic", "A* with the Eucledian distance heuristic"};
   string algoChoice;

   cout << "Enter your choice of algorithm" << endl;
   for (int i = 0; i < algorithms.size(); i++) {
      cout << algorithms[i] << endl;
   }

   cin >> algoChoice;
   cout << endl;
   return algoChoice;
}
