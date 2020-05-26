#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "container.h"

class Container;

class Algorithm {
   public:
      Algorithm() {}

      virtual void search(Container* container) = 0;      
};

#endif
