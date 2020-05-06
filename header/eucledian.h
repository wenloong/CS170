#ifndef EUCLEDIAN_H
#define EUCLEDIAN_H

#include "algorithm.h"

class Algorithm;

class Eucledian:public Algorithm {
   public:
      void search(Container* container);

   private:
      vector<vector<char>> puzzle;

};

void Eucledian::search(Container* container) {
   cout << "Eucledian" << endl;
}

#endif
