#ifndef OPERATOR_H
#define OPERATOR_H

#include "puzzle.h"

using namespace std;

class Operator: public Puzzle {
   public:
      Operator(Puzzle* puzzle) {
         this->puzzle = puzzle;
      }

   private:
      
};

#endif

