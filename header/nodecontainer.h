#ifndef NODECONTAINER_H
#define NODECONTAINER_H

#include "puzzle.h"
#include "algorithm.h"
#include "container.h"

using namespace std;

struct Node {
      Puzzle data;
      Node* next;
};

class NodeContainer: public Container {
   public:
      NodeContainer() {
         head = NULL;
         tail = NULL;
      }

      void create_node(Puzzle state);
      void print();
      void set_algorithm_function(Algorithm* algo_function);
      void search();

   private:
      Node *head, *tail;
};

void NodeContainer::create_node(Puzzle state) {
   Node *temp = new Node;
   temp->data = state;
   temp->next = NULL;

   if (head == NULL) {
      head = temp;
      tail = temp;
      temp = NULL;
   } else {
      tail->next = temp;
      tail = temp;
   }
}

void NodeContainer::print() {
   Node* temp = new Node;
   temp = head;

   while (temp != NULL) {
      temp->data.display();
      temp = temp->next;
   }
}

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
