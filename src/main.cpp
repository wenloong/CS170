#include <iostream>
#include <string>
#include <vector>

#include "../header/puzzle.h"
#include "../header/algorithm.h"
#include "../header/uniform.h"
#include "../header/misplaced.h"
#include "../header/eucledian.h"
#include "../header/container.h"
#include "../header/nodecontainer.h"

using namespace std;

int puzzleChoiceInput();
int algoChoiceInput();
void puzzleGenInput();
void convert_to_row(string input, int row);

int main() {
   Puzzle init;

   printWelcome();
   
   /* Puzzle Choice */
   if (puzzleChoiceInput() == 2) {
      userProblem.puzzleGenInput();
   }

   NodeContainer* container = new NodeContainer();

   /* Algorithm Choice */
   int algoChoice = algoChoiceInput();
   if (algoChoice == 1)
      container->set_algorithm_function(new Uniform());
   else if (algoChoice == 2)
      container->set_algorithm_function(new Misplaced());
   else if (algoChoice == 3)
      container->set_algorithm_function(new Eucledian());
   else
      cout << "Error: Invalid Algorithm Choice, exiting program" << endl;
  
   container->search();
}

void printWelcome() {
   int sid = 862154819;

   cout << "Welcome to \"" << sid << "\" 8 puzzle solver." << endl;
}

int puzzleChoiceInput() {
   int userInput;
   
   cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
   cout << "[guestUser@root]$ ";
   cin >> userInput;
   cout << endl;
   
   return userInput;
}

int algoChoiceInput() {
   int userInput;
   
   cout << "Enter your choice of algorithm" << endl;
   cout << "1. Uniform Cost Search" << endl;
   cout << "2. A* with the Misplaced Tile Heuristic" << endl;
   cout << "3. A* with the Eucledian distance Heuristic" << endl;
   cout << "[guestUser@root]$ ";
   cin >> userInput;
   cout << endl;
   
   return userInput;
}

void puzzleGenInput() {
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

   init = new Puzzle(this->topRow, this->midRow, this->botRow);
}


void convert_to_row(string input, int row) {
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
