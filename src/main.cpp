#include <iostream>
#include <string>
#include <vector>

#include "../header/problem.h"
#include "../header/algorithm.h"
#include "../header/uniform.h"
#include "../header/misplaced.h"
#include "../header/eucledian.h"
#include "../header/container.h"
#include "../header/nodecontainer.h"

using namespace std;

int main() {
   Problem userProblem;

   userProblem.printWelcome();

   /* Puzzle Choice */
   userProblem.puzzleChoiceInput();
   if (userProblem.getPuzzleChoice() == 2) {
      userProblem.puzzleGenInput();
   }

   NodeContainer* container = new NodeContainer();

   /* Algorithm Choice */
   userProblem.algoChoiceInput();
   if (userProblem.getAlgoChoice() == 1)
      container->set_algorithm_function(new Uniform());
   else if (userProblem.getAlgoChoice() == 2)
      container->set_algorithm_function(new Misplaced());
   else if (userProblem.getAlgoChoice() == 3)
      container->set_algorithm_function(new Eucledian());
   else
      cout << "Error: Invalid Algorithm Choice, exiting program" << endl;
  
   container->search();
}
