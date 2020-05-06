#ifndef CONTAINER_H
#define CONTAINER_H

#include "problem.h"
#include "algorithm.h"

class Problem;
class Algorithm;

class Container {
   protected:
      Algorithm* algo_function;

   public:
      Container() : algo_function(nullptr) {};
      Container(Algorithm* function) : algo_function(function) {};

      void set_algorithm_function(Algorithm* algo_function);
};

#endif
