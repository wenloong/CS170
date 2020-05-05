#include <iostream>
#include <string>
#include <vector>

#include "../header/problem.h"

using namespace std;

int main() {
   Problem userProblem;

   Problem.printWelcome();
   Problem.puzzleChoiceInput();
   Problem.algoChoiceInput();
   Problem.printPuzzle();
}
