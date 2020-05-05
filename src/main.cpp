#include <iostream>
#include <string>
#include <vector>

#include "../header/problem.h"

using namespace std;

int main() {
   Problem userProblem;

   userProblem.printWelcome();
   userProblem.puzzleChoiceInput();

   if (userProblem.getPuzzleChoice() == 2) {
      userProblem.puzzleGenInput();
   }

   userProblem.algoChoiceInput();
   userProblem.printPuzzle();
}
