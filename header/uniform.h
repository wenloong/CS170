#ifndef UNIFORM_H
#define UNIFORM_H

#include "algorithm.h"

class Algorithm;
class Problem;

class Uniform:public Algorithm {
   public:
      void search(Container* container);

   private:
      vector<vector<char>> puzzle;
};

void Uniform::search(Container* container) {
   cout << "Uniform" << endl;
}

#endif
