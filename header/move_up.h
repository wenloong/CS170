#ifndef MOVE_UP_H
#define MOVE_UP_H

#include "operator.h"
#include "problem.h"

class Move_Up: public Operator {
   public:
      Move_Up(Problem* puzzle): Operator(puzzle) {
         this->puzzle = puzzle;
      }

   private:
      Problem* puzzle;
};

#endif
