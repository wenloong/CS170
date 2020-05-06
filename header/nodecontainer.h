#ifndef VECTORCONTAINER_H
#define VECTORCONTAINER_H

#include <vector>

#include "problem.h"
#include "algorithm.h"
#include "container.h"

using namespace std;

class NodeContainer: public Container {
   public:
      Problem state;
      NodeContainer* up;
      NodeContainer* down;
      NodeContainer* left;
      NodeContainer* right;

      void set_algorithm_function(Algorithm* algo_function);
      void search();

   private:
      vector<Problem*> container;
};

void NodeContainer::set_algorithm_function(Algorithm* algo_function) {
   this->algo_function = algo_function;
}

void NodeContainer::search() {
   if (algo_function == NULL)
      throw "ERROR: Algorithm function is NULL";
   else
      algo_function->search(this);
}

#endif
