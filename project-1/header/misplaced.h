#ifndef MISPLACED_H
#define MISPLACED_H

#include "algorithm.h"
#include "container.h"
#include "puzzle.h"
#include "operator.h"
#include "nodecontainer.h"

struct CompareCostMisplaced {
   bool operator() (Operator* p1, Operator* p2) {
      return (p1->getPuzzleState().calculate_misplaced() + p1->getG()) > (p2->getPuzzleState().calculate_misplaced() + p2->getG());
   }
};

class Misplaced:public Algorithm {
   public:
      void search(Container* container);
      bool is_visited(vector<Operator*> visited, Puzzle state);
      int calculate_misplaced(Puzzle puzzle);
   private:

};

void Misplaced::search(Container* container) {
   cout << "A* Misplaced Heuristic Search" << endl;
   
   // First define initial state and goal state
   Puzzle init = container->return_tail();
   Puzzle* goal = new Puzzle('1', '2', '3', '4', '5', '6', '7', '8', 'b');

   // If the program detects that the initial state is already the goal state, end the program
   if (init.compare(goal) == true) {
      cout << "Goal!" << endl;
      init.display();
      return;
   }

   Operator* child = new Operator(init);
   priority_queue<Operator*, vector<Operator*>, CompareCostMisplaced> frontier;
   vector<Operator*> visited;
   int num_nodes = 0;
   int max_nodes = 0;
 
   frontier.push(child);
   
   // While the frontier still contains node, keep looping through it
   while (!frontier.empty()) {
      Operator* current_state = frontier.top();
      frontier.pop();
      container->create_node(current_state->getPuzzleState());
  
      // If the current state is the goal state, we can break the loop and print the answer
      if (current_state->compare(goal)) {
         container->remove_head();
         container->print();
         cout << "Goal!" << endl;
         cout << "To solve this problem the search algorithm expanded a total of " << num_nodes << " nodes." << endl;
         cout << "The maximum number of nodes in the queue at any one time: " << max_nodes << "." << endl;
         break;
      }

      Operator* up = new Operator(current_state->getPuzzleState());
      Operator* down = new Operator(current_state->getPuzzleState());
      Operator* left = new Operator(current_state->getPuzzleState());
      Operator* right = new Operator(current_state->getPuzzleState());
      
      visited.push_back(current_state);

      if (up->move_up()) {
         if (!is_visited(visited, up->getPuzzleState())) {
            frontier.push(up);
            num_nodes++;
         }
      }

     if (down->move_down()) {
         if (!is_visited(visited, down->getPuzzleState())) {
            frontier.push(down);
            num_nodes++;
         }
      }

      if (left->move_left()) {
         if (!is_visited(visited, left->getPuzzleState())) {
            frontier.push(left);
            num_nodes++;
         }
      }

      if (right->move_right()) {
         if (!is_visited(visited, right->getPuzzleState())) {
            frontier.push(right);
            num_nodes++;
         }
      }

      if (frontier.size() > max_nodes)
         max_nodes = frontier.size();  

      //cout << "Press enter to continue";
      //cin.ignore(numeric_limits<streamsize>::max(), '\n');
   }
}

bool Misplaced::is_visited(vector<Operator*> visited, Puzzle state) {
   for (int i = 0; i < visited.size(); i++) {
      if (visited[i]->compare(state))
         return true;
   }

   return false;
}

#endif
