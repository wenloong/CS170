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
#include "../header/operator.h"

using namespace std;

void printWelcome();
int puzzleChoiceInput();
int algoChoiceInput();
vector<char> puzzleTop();
vector<char> puzzleMid();
vector<char> puzzleBot();
vector<char> convert_to_row(string input);

int main() {
   Puzzle init;
   vector<char> top, mid, bot;

   printWelcome();
   
   /* Puzzle Choice */
   if (puzzleChoiceInput() == 2) {
      top = puzzleTop();
      mid = puzzleMid();
      bot = puzzleBot();
      init = Puzzle(top, mid, bot);
   } else {
      init = Puzzle();
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

   Operator* test = new Operator(init);
   test.display();

   container->search();
   init.display();
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

vector<char> puzzleTop() {
   string row;
   vector<char> temp;

   cout << "Enter your puzzle, use a zero to represent to blank" << endl;
   cout << "Enter the first row, use space or tabs between numbers ";
   cin.ignore(1);
   getline(cin, row);
   return convert_to_row(row);
}

vector<char> puzzleMid() {
   string row;
   vector<char> temp;

   cout << "Enter the second row, use space or tabs between numbers ";
   getline(cin, row);
   return convert_to_row(row);
}

vector<char> puzzleBot() {
   string row;
   vector<char> temp;

   cout << "Enter the third row, use space or tabs between numbers ";
   getline(cin, row);
   return convert_to_row(row);
}

vector<char> convert_to_row(string input) {
   input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
   char col_1 = input[0];
   char col_2 = input[1];
   char col_3 = input[2];

   vector<char> temp;
   temp.push_back(col_1);
   temp.push_back(col_2);
   temp.push_back(col_3);

   return temp;
}
