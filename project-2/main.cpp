#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

#include "mlsearch.h"

using namespace std;

int main() {
   string filename;
   int algoChoice;
    
   cout << BOLD << "Enter the name of the file you want to test: " << RESET;
   cin >> filename;
   cout << endl;
   
   mlSearch* search_algo = new mlSearch(filename);
   cout << YELLOW << "Choose an algorithm" << endl;
   cout << "1) Forward Selection" << endl;
   cout << "2) Backward Selection" << endl;
   cout << RESET << endl;

   cout << BOLD << "Enter your selection: " << RESET;
   cin >> algoChoice;
   cout << endl;

   double accuracy = search_algo->nearest_neighbour();
   cout << accuracy << "%" << endl << endl;

   cout << endl;
   if (algoChoice == 1) { search_algo->forward_selection(); } 
   else if (algoChoice == 2) { search_algo->backward_elimination(); }
}
