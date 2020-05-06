#ifndef MOVE_UP_H
#define MOVE_UP_H

#include "operator.h"
#include "puzzle.h"

class Move_Up: public Operator {
   public:
      Move_Up(Puzzle* puzzle): Operator(puzzle) {
         this->puzzle = puzzle;
      }

   private:
      Puzzle* puzzle;
};

#endif
