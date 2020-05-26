#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
   Puzzle* goal_state = new Puzzle('1', '2', '3', '4', '5', '6', '7', '8', 'b');
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
   container->create_node(init);

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

   cout << "\033[1;37mWelcome to \"\033[0m" << sid << "\033[1;37m\" 8 puzzle solver.\033[0m" << endl;
}

int puzzleChoiceInput() {
   int userInput;
   
   cout << "\033[21;33mType \"1\" to use a default puzzle, or \"2\" to enter your own puzzle.\033[0m" << endl;
   cout << "\033[21;32m[guestUser@root]$ \033[0m";
   cin >> userInput;
   cout << endl;
   
   return userInput;
}

int algoChoiceInput() {
   int userInput;
   
   cout << "\033[21;31mEnter your choice of algorithm\033[0m" << endl;
   cout << "\033[21;36m1. Uniform Cost Search\033[0m" << endl;
   cout << "\033[21;36m2. A* with the Misplaced Tile Heuristic\033[0m" << endl;
   cout << "\033[21;36m3. A* with the Eucledian distance Heuristic\033[0m" << endl;
   cout << "\033[21;32m[guestUser@root]$ \033[0m";
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
