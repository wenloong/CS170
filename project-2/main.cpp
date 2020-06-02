#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

char RESET[] = { 0x1b, '[', '0', ';', '3', '7', 'm', 0 };
char BOLD[] = { 0x1b, '[', '1', ';', '3', '7', 'm', 0 };
char RED[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char GREEN[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
char YELLOW[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };

void normalizeData(vector<vector<double>> data);
void displaySubset(vector<int> feature, int accu);
double leave_one_out(vector<vector<double>> data, vector<int> currentFeatures ,int newFeature, bool isForward);
double nearest_neighbour(vector<vector<double>> data, int numFeatures);
void forward_selection(vector< vector<double> > data);
vector<int> removeFeature(vector<int> currentFeatures, int removedFeature);
void backward_elimination(vector< vector<double>> data);

int main() {
   string filename, line;
   vector<vector<double>> data;
   double dataInput = 0;
   int algoChoice;
    
   cout << BOLD << "Enter the name of the file you want to test: " << RESET;
   cin >> filename;
   cout << endl;
    
   ifstream file(filename.c_str());
   if (!file.is_open()) {
      cout << RED << "Error: unable to open file." << RESET << endl;
      exit(1);
   }

   while (getline(file, line)) {
      stringstream lineStream(line);
      vector<double> instance;
			
      while (lineStream >> dataInput) {
         instance.push_back(dataInput);
      }
      data.push_back(instance);
   }
   file.close();
	
   cout << YELLOW << "Choose an algorithm" << endl;
   cout << "1) Forward Selection" << endl;
   cout << "2) Backward Selection" << endl;
   cout << RESET << endl;

   cout << BOLD << "Enter your selection: " << RESET;
   cin >> algoChoice;
   cout << endl;

   cout << "This data has " << data[0].size() - 1 << " features (not including the class attribute), with " << data.size() << " instances." << endl << endl;

   double accuracy = nearest_neighbour(data, data[0].size());
   cout << accuracy << "%" << endl << endl;


   cout << endl;
   if (algoChoice == 1) { forward_selection(data); } 
   else if (algoChoice == 2) { backward_elimination(data); }
}


/*
   To normalize our data, we will use the min max normalization method as opposed to
   the z-score normalization
*/
void normalizeData(vector<vector<double>> data) {
   vector<double> fMin;
   vector<double> fMax;

   for (int i = 0; i < data[0].size(); i++) {
      fMin.push_back(data[0][i]);
      fMax.push_back(data[0][i]);
   }

   for (int i = 0; i < data.size(); i++) {
      for (int j = 0; j < data[0].size(); j++) {
         if (data[i][j] < fMin[j]) { fMin[j] = data[i][j]; }
         if (data[i][j] > fMax[j]) { fMax[j] = data[i][j]; }
      }
   }

   for (int i = 0; i < data.size(); i++) {
      for (int j = 0; i < data[0].size(); j++) {
         data[i][j] = (data[i][j] - fMin[j]) / (fMax[j] - fMin[j]);
      }
   }
}

void displaySubset(vector<int> feature) {
   for (int i = 0; i < feature.size() - 1; i++) {
      cout << feature[i] << ", ";
   }
   cout << feature[feature.size() - 1] << "} was the best, with accuracy ";
}

double leave_one_out(vector<vector<double>> data, vector<int> currentFeatures ,int newFeature, bool isForward) {
   int numCorrect = 0; // number of correct classifications
   double temp, min_dist, dist = 0;
   vector <double> testingSet;
   vector <double> nearest; // nearest neighbor (closest point in training set)
	
   for (int i = 0; i < data.size(); i++) {	
      testingSet = data[i]; 
      min_dist = 1000000;
      dist = 0;

      for (int j = 0; j < data.size(); j++) { 
         if (j != i) { 
            temp = 0;
		 
            for (int k = 0; k < currentFeatures.size(); k++) {
               temp += (pow(testingSet[currentFeatures[k]] - data[j][currentFeatures[k]], 2));
	         }
            if (isForward) {
                  temp += (pow(testingSet[newFeature] - data[j][newFeature], 2));
            }
            dist = sqrt(temp);
		 
            if (dist < min_dist) { 
               min_dist = dist;
               nearest = data[j];
            }
         }	
      }	

      // if predicted/actual classifications are the same, increment numCorrect
      if (nearest[0] == 1 && testingSet[0] == 1) 
         ++numCorrect;
      else if (nearest[0] == 2 && testingSet[0] == 2)
         ++numCorrect;
   }
   return (double)numCorrect / (double)data.size();
}

double nearest_neighbour(vector<vector<double>> data, int numFeatures) {
   vector<int> currentFeatures;

   for (int i = 1; i < numFeatures; i++)
      currentFeatures.push_back(i);
	
   cout << "Running nearest neighbor with all " << numFeatures - 1 << " features, using \"leaving-one-out\" evaluation, I get an accuracy of ";
   double accuracy = leave_one_out(data,currentFeatures,0,false);

   return leave_one_out(data,currentFeatures,0,false);
}

void forward_selection(vector<vector<double> > data) {
   vector<int> currentFeatures; // current set of features being tested
   vector<int> bestFeatures; // set of features with highest accuracy 
   double accuracy = 0; 
   double maxAccuracy = 0; // highest accuracy to a certain point
   double globalMaxAccuracy = 0; // highest accuracy overall
   int addedFeature;
	
   for (int i = 1; i < data[0].size(); i++) {
      maxAccuracy = 0;
      
      for (int j = 1; j < data[0].size(); j++) { 
         if (find(currentFeatures.begin(), currentFeatures.end(), j) == currentFeatures.end()) {
            accuracy = leave_one_out(data,currentFeatures, j, true);
				
            cout << "Using feature(s) {";
            for (int k = 0; k < currentFeatures.size(); k++) 
               cout << currentFeatures[k] << ",";
            cout << j << "} accuracy is ";
            cout << accuracy * 100 << "%" << endl;

            if (accuracy > maxAccuracy) {
               addedFeature = j;
               maxAccuracy = accuracy;
            }
         }
      }
	   
      currentFeatures.push_back(addedFeature);
      cout << endl;

      if (maxAccuracy > globalMaxAccuracy) {
         globalMaxAccuracy = maxAccuracy;
         bestFeatures = currentFeatures;
      } else {
         cout << RED << "(Warning, accuracy has decreased! Continuing search in case of local maxima)" << endl << RESET;
      }
	   
      cout << YELLOW;
      cout << "Feature set {";
      displaySubset(currentFeatures);
      cout << maxAccuracy * 100 << "%" << endl << endl << RESET;
   }

   cout << GREEN;
   cout << "Finished search! The best feature subset is {";
   displaySubset(bestFeatures);
   cout << globalMaxAccuracy * 100 << "%" << endl << RESET;
}

// helper function for backward elimination (removes feature from vector)
vector<int> removeFeature(vector<int> currentFeatures, int removedFeature) {
   for (int i = 0; i < currentFeatures.size(); i++) {
      if (currentFeatures[i] == removedFeature) {
         currentFeatures.erase(currentFeatures.begin() + i);
         return currentFeatures;
      }
   }
   return currentFeatures;
}

void backward_elimination(vector<vector<double>> data) {
   vector <int> currentFeatures;
   vector <int> bestFeatures;
   double accuracy = 0;
   double maxAccuracy = 0;
   double globalMaxAccuracy = 0;

   int removedFeature;
		
   for (int i = 1; i < data[0].size(); i++) 
      currentFeatures.push_back(i);
	
   for (int i = 1; i < data[0].size() - 1; i++) {
      maxAccuracy = 0;
	   
      for (int j = 1; j < data[0].size(); j++) { 
         if (find(currentFeatures.begin(), currentFeatures.end(), j) != currentFeatures.end()) {
            //vector<int> temp = removeFeature(currentFeatures, removedFeature);
            vector<int> temp = currentFeatures;
            temp.erase(remove(temp.begin(), temp.end(), j), temp.end());

            cout << "Using feature(s) {";
            for (int k = 0; k < temp.size() - 1; k++)
               cout << temp.at(k) << ",";
            cout << temp.at(temp.size() - 1) << "} accuracy is ";
		 
	         accuracy = leave_one_out(data, temp, j, false);
            cout << accuracy * 100 << "%" << endl;
            if (accuracy > maxAccuracy) {
               maxAccuracy = accuracy;
            }
         }
      }
	   
      //currentFeatures = removeFeature(currentFeatures, removedFeature);
      currentFeatures.erase(remove(currentFeatures.begin(), currentFeatures.end(), globalMaxAccuracy), currentFeatures.end());
      cout << endl;
	   
      if (maxAccuracy > globalMaxAccuracy) {
         globalMaxAccuracy = maxAccuracy;
         bestFeatures = currentFeatures;
      } else {
         cout << RED << "(Warning, accuracy has decreased! Continuing search in case of local maxima)" << endl << RESET;
      }

      cout << YELLOW;
      cout << "Feature set {";
      displaySubset(currentFeatures);
      cout << maxAccuracy * 100 << "%" << endl << endl << RESET;
   }

   cout << GREEN;
   cout << "Finished search! The best feature subset is {";
   displaySubset(bestFeatures);
   cout << globalMaxAccuracy * 100 << "%" << endl << RESET;
}
