#ifndef MOVE_LEFT_H
#define MOVE_LEFT_H

#include "operator.h"
#include "puzzle.h"

class Move_Left: public Operator {
   public:
      Move_Left(Puzzle* puzzle): Operator(puzzle) {
         this->puzzle = puzzle;
      }

   private:
      Puzzle* puzzle;
};

#endif
