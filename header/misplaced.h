#ifndef MISPLACED_H
#define MISPLACED_H

#include "algorithm.h"
#include "container.h"
#include "puzzle.h"
#include "operator.h"

class Misplaced:public Algorithm {
   public:
      void search(Container* container);
      int calculate_misplaced(Puzzle puzzle);
   private:

};

void Misplaced::search(Container* container) {
   cout << "A* Misplaced Heuristic Search" << endl;
   
   Puzzle init = container->return_tail();
   Puzzle* goal = new Puzzle('1', '2', '3', '4', '5', '6', '7', '8', 'b');

   if (init.compare(goal) == true) {
      cout << "Goal!" << endl;
      init.display();
      return;
   }

   Operator* move = new Operator(init);
   move->display();

   if (move->move_down()) {
   container->create_node(move->getPuzzleState());
   cout << endl;
   move->display();
   }

   move->move_left();
   container->create_node(move->getPuzzleState());
   cout << endl;
   move->display();

   move->move_up();
   cout << endl;
   move->display();

   move->move_right();
   cout << endl;
   move->display();

   move->move_down();
   cout << endl;
   move->display(); 
 
   cout << endl << endl;
   cout << "Displaying results: " << endl;
   container->print();  
}

int Misplaced::calculate_misplaced(Puzzle puzzle) {
   int count_misplaced;

   if (puzzle.getTL() != '1' && puzzle.getTL() != 'b')
      count_misplaced++;
   if (puzzle.getTM() != '2' && puzzle.getTM() != 'b')
      count_misplaced++;
   if (puzzle.getTR() != '3' && puzzle.getTR() != 'b')
      count_misplaced++;
   if (puzzle.getML() != '4' && puzzle.getML() != 'b')
      count_misplaced++;
   if (puzzle.getMM() != '5' && puzzle.getMM() != 'b')
      count_misplaced++;
   if (puzzle.getMR() != '6' && puzzle.getMR() != 'b')
      count_misplaced++;
   if (puzzle.getBL() != '7' && puzzle.getBL() != 'b')
      count_misplaced++;
   if (puzzle.getBM() != '8' && puzzle.getBM() != 'b')
      count_misplaced++;   
   if (puzzle.getBR() != 'b' && puzzle.getBR() != 'b')
      count_misplaced++;

   return count_misplaced;
}

#endif
