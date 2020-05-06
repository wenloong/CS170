#ifndef MOVE_DOWN_H
#define MOVE_DOWN_H

#include "operator.h"
#include "problem.h"

class Move_Down: public Operator {
   public:
      Move_Down(Problem* puzzle): Operator(puzzle) {
         this->puzzle = puzzle;
      }

   private:
      Problem* puzzle;
};

#endif
