#ifndef MISPLACED_H
#define MISPLACED_H

#include "algorithm.h"
#include "container.h"

class Misplaced:public Algorithm {
   public:
      void search(Container* container);

   private:

};

void Misplaced::search(Container* container) {
   cout << " MIS" << endl;
}

#endif
