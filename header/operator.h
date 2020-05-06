#ifndef OPERATOR_H
#define OPERATOR_H

#include "problem.h"

using namespace std;

class Operator: public Problem {
   public:
      Operator(Problem* puzzle) {
         this->puzzle = puzzle;
      }

   private:
      
};

#endif

