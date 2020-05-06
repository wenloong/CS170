#ifndef MOVE_DOWN_H
#define MOVE_DOWN_H

#include "operator.h"
#include "puzzle.h"

class Move_Down: public Operator {
   public:
      Move_Down(Puzzle* puzzle): Operator(puzzle) {
         this->puzzle = puzzle;
      }

   private:
      Puzzle* puzzle;
};

#endif
