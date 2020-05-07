#ifndef EUCLEDIAN_H
#define EUCLEDIAN_H

#include "algorithm.h"

class Algorithm;

class Eucledian:public Algorithm {
   public:
      void search(Container* container);
      int calculate_eucledian(Puzzle puzzle);
   private:
      vector<vector<char>> puzzle;

};

void Eucledian::search(Container* container) {
   cout << "A* Eucledian Heuristic Search" << endl;

   Puzzle init = container->return_tail();
   Puzzle* goal = new Puzzle('1', '2', '3', '4', '5', '6', '7', '8', 'b');

   if (init.compare(goal) == true) {
      cout << "Goal!" << endl;
      init.display();
      return;
   }


}

int Eucledian::calculate_eucledian(Puzzle puzzle) {
   int count_eucledian;

   if (puzzle.getTL() != '1' && puzzle.getTL() != 'b')
      count_eucledian += abs((puzzle.getTL() - 1) % 3 - (0 % 3)) + abs(floor((puzzle.getTL() - 1) / 3) - floor(0/3));
   if (puzzle.getTM() != '2' && puzzle.getTM() != 'b')
      count_eucledian += abs((puzzle.getTM() - 1) % 3 - (1 % 3)) + abs(floor((puzzle.getTM() - 1) / 3) - floor(1/3)); 
   if (puzzle.getTR() != '3' && puzzle.getTR() != 'b')
      count_eucledian += abs((puzzle.getTR() - 1) % 3 - (2 % 3)) + abs(floor((puzzle.getTR() - 1) / 3) - floor(2/3)); 
   if (puzzle.getML() != '4' && puzzle.getML() != 'b')
      count_eucledian += abs((puzzle.getML() - 1) % 3 - (3 % 3)) + abs(floor((puzzle.getML() - 1) / 3) - floor(3/3)); 
   if (puzzle.getMM() != '5' && puzzle.getMM() != 'b')
      count_eucledian += abs((puzzle.getMM() - 1) % 3 - (4 % 3)) + abs(floor((puzzle.getMM() - 1) / 3) - floor(4/3)); 
   if (puzzle.getMR() != '6' && puzzle.getMR() != 'b')
      count_eucledian += abs((puzzle.getMR() - 1) % 3 - (5 % 3)) + abs(floor((puzzle.getMR() - 1) / 3) - floor(5/3)); 
   if (puzzle.getBL() != '7' && puzzle.getBL() != 'b')
      count_eucledian += abs((puzzle.getBL() - 1) % 3 - (6 % 3)) + abs(floor((puzzle.getBL() - 1) / 3) - floor(6/3)); 
   if (puzzle.getBM() != '8' && puzzle.getBM() != 'b')
      count_eucledian += abs((puzzle.getBM() - 1) % 3 - (7 % 3)) + abs(floor((puzzle.getBM() - 1) / 3) - floor(7/3));  
   if (puzzle.getBR() != 'b' && puzzle.getBR() != 'b')
      count_eucledian += abs((puzzle.getBR() - 1) % 3 - (8 % 3)) + abs(floor((puzzle.getBR() - 1) / 3) - floor(8/3)); 

   return count_eucledian;
}

#endif
