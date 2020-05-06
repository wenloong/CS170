#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

#include "puzzle.h"

using namespace std;

class Problem {
   public:
      Puzzle* initial_state;
      Puzzle* goal_state = new Puzzle('1', '2', '3', '4', '5', '6', '7', '8', 'b');
      vector<char> topRow, midRow, botRow;

      /* Display Functions */
      void printWelcome();
      void printPuzzle();

      /* User Input Functions */
      void puzzleChoiceInput();
      void algoChoiceInput();
      void puzzleGenInput();

      /* Helper Functions */
      void convert_to_row(string input, int row);
      void convert_to_puzzle(vector<char> top, vector<char> mid, vector<char> bot);

      /* Getters */
      int getPuzzleChoice();
      int getAlgoChoice();

   private:
      int puzzleChoice = 1;                 // Default puzzle choice is 1
      int algoChoice = 1;                   // Default algorithm choice is Uniform Cost Search, 1 
      //vector<char> topRow, midRow, botRow;  // Define seperate rows to use for 2D vector
};

#endif
