#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define ROW_SIZE 3
#define COL_SIZE 3

class Problem {
   public:
      vector<char> row;
      vector<vector<char>> puzzle {{'0', '1', '2'},
                                   {'4', '8', 'b'},
                                   {'7', '6', '5'}};

      /* Display Functions */
      void printWelcome();
      void printPuzzle();

      /* User Input Functions */
      void puzzleChoiceInput();
      void algoChoiceInput();
      void puzzleGenInput();

      /* Helper Functions */
      void convert_to_row(string in, int row);
      void convert_to_puzzle(vector<char> top, vector<char> mid, vector<char> bot);

      /* Getters */
      int getPuzzleChoice();
      int getAlgoChoice();

   private:
      int puzzleChoice = 1;                 // Default puzzle choice is 1
      int algoChoice = 1;                   // Default algorithm choice is Uniform Cost Search, 1 
      vector<char> topRow, midRow, botRow;  // Define seperate rows to use for 2D vector
}

#endif
