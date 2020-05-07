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

class Node_LL {
   public:
      Node_LL() {
         head = NULL;
         tail = NULL;
      }

      void create_node(Puzzle state) {
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

      void print() {
         Node* temp = new Node;
         temp = head;

         while (temp != NULL) {
            temp->data.display();
            cout << endl;
            temp = temp->next;
         }
      }

      Puzzle get_tail() {
         Node* temp = new Node;
         temp = tail;
         return temp->data;
      }

   private:
      Node *head, *tail;
};

class NodeContainer: public Container {
   public:

      void create_node(Puzzle state);
      void print();
      void set_algorithm_function(Algorithm* algo_function);
      void search();
      Puzzle return_tail();

   private:
      Node_LL puzzle_obj;
};

void NodeContainer::create_node(Puzzle state) {
   puzzle_obj.create_node(state);
}

void NodeContainer::print() {
   puzzle_obj.print();
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

Puzzle NodeContainer::return_tail() {
   return puzzle_obj.get_tail();
}

#endif
