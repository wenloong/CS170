#ifndef CONTAINER_H
#define CONTAINER_H

#include "algorithm.h"

class Puzzle;
class Algorithm;

class Container {
   protected:
      Algorithm* algo_function;

   public:
      Container() : algo_function(nullptr) {};
      Container(Algorithm* function) : algo_function(function) {};

      void set_algorithm_function(Algorithm* algo_function);
      virtual void create_node(Puzzle state) = 0;
      virtual void remove_head() = 0;
      virtual void print() = 0;
      virtual void search() = 0;
      virtual Puzzle return_tail() = 0;
};

#endif
