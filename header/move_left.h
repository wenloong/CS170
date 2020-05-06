#ifndef MOVE_LEFT_H
#define MOVE_LEFT_H

#include "operator.h"
#include "problem.h"

class Move_Left: public Operator {
   public:
      Move_Left(Problem* puzzle): Operator(puzzle) {
         this->puzzle = puzzle;
      }

   private:
      Problem* puzzle;
};

#endif
