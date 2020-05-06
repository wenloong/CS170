#ifndef MOVE_RIGHT_H
#define MOVE_RIGHT_H

#include "operator.h"
#include "puzzle.h"

class Move_Right: public Operator {
   public:
      Move_Right(Puzzle* puzzle): Operator(puzzle) {
         this->puzzle = puzzle;
      }

   private:
      Puzzle* puzzle;
};

#endif
