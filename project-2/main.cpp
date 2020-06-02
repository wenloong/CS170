#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

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

double leave_one_out(vector<vector<double>> data, vector<int> currentFeatures ,int newFeature, bool isForward) {
   int numCorrect = 0; // number of correct classifications
   double tmp, min_dist, dist = 0;
   vector <double> testingSet;
   vector <double> nearest; // nearest neighbor (closest point in training set)
	
   for (int i = 0; i < data.size(); i++) {	
      testingSet = data[i]; 
      min_dist = 1000000;
      dist = 0;

      for (int j = 0; j < data.size(); j++) { 
         if (j != i) { 
            tmp = 0;
		 
            for (int k = 0; k < currentFeatures.size(); k++) {
               tmp += (pow(testingSet[currentFeatures[k]] - data[j][currentFeatures[k]], 2));
	    }
            if (isForward) {
                  tmp += (pow(testingSet[newFeature] - data[j][newFeature], 2));
	    }
            dist = sqrt(tmp);
		 
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

void nearest_neighbour(vector<vector<double>> data, int numFeatures) {
   vector<int> currentFeatures;

   for (int i = 1; i < numFeatures; i++)
      currentFeatures.push_back(i);
	
   double accuracy = leave_one_out(data,currentFeatures,0,false);
				
   cout << "Running nearest neighbor with all " << numFeatures - 1 << " features, using \"leaving-one-out\" evaluation, I get an accuracy of ";
   cout << leave_one_out(data,currentFeatures,0,false) << "%" << endl << endl;
}

void forwardSelection(vector< vector<double> > data) {
   vector<int> currentFeatures; // current set of features being tested
   vector<int> bestFeatures; // set of features with highest accuracy 
   double accuracy = 0; 
   double bestAccuracy = 0; // highest accuracy to a certain point
   double maxAccuracy = 0; // highest accuracy overall
   int addedFeature;
	
   for (int i = 1; i < data.at(0).size(); i++) {
      bestAccuracy = 0;
      
      for (int j = 1; j < data.at(0).size(); j++) { 
         if (find(currentFeatures.begin(), currentFeatures.end(), j) == currentFeatures.end()) {
            accuracy = leave_one_out(data,currentFeatures, j, true);
				
            cout << "\tUsing feature(s) {";
            for (int k = 0; k < currentFeatures.size(); k++) 
               cout << currentFeatures.at(k) << ",";
            cout << j << "} accuracy is ";
            cout << accuracy * 100 << "%" << endl;

            if (accuracy > bestAccuracy) {
               addedFeature = j;
               bestAccuracy = accuracy;
            }
         }
      }
	   
      currentFeatures.push_back(addedFeature);
      cout << endl;

      if (bestAccuracy > maxAccuracy) {
         maxAccuracy = bestAccuracy;
         bestFeatures = currentFeatures;
      } else {
         cout << "(Warning, accuracy has decreased! Continuing search in case of local maxima)" << endl;
      }
	   
      cout << "Feature set {";
      for (int k = 0; k < currentFeatures.size() - 1; k++)
         cout << currentFeatures.at(k) << ",";
      cout << currentFeatures.at(currentFeatures.size() - 1);
      cout <<"} was best, accuracy is ";
      cout << bestAccuracy * 100 << "%" << endl << endl;
   }
	
   cout << "Finished search!! The best feature subset is {";
   for (int k = 0; k < bestFeatures.size() - 1; k++)
      cout << bestFeatures.at(k) << ",";
   cout << bestFeatures.at(bestFeatures.size() - 1);
   cout << "}, which has an accuracy of " << maxAccuracy * 100 << "%" << endl;
}

// helper function for backward elimination (removes feature from vector)
vector <int> removeFeature(vector<int> currentFeatures, int removedFeature) {
   for (int i = 0; i < currentFeatures.size(); i++) {
      if (currentFeatures.at(i) == removedFeature) {
         currentFeatures.erase(currentFeatures.begin() + i);
         return currentFeatures;
      }
   }
   return currentFeatures;
}

void backwardElim(vector< vector<double> > data) {
   vector <int> currentFeatures;
   vector <int> bestFeatures;
   double accuracy = 0;
   double bestAccuracy = 0;
   double maxAccuracy = 0;
   int removedFeature;
		
   for (int i = 1; i < data.at(0).size(); i++) 
      currentFeatures.push_back(i);
	
   for (int i = 1; i < data.at(0).size() - 1; i++) {
      bestAccuracy = 0;
	   
      for (int j = 1; j < data.at(0).size(); j++) { 
         if (find(currentFeatures.begin(), currentFeatures.end(), j) != currentFeatures.end()) {
            vector <int> tmp = removeFeature(currentFeatures, j);
            cout << "\tUsing feature(s) {";
            for (int k = 0; k < tmp.size() - 1; k++)
               cout << tmp.at(k) << ",";
            cout << tmp.at(tmp.size() - 1) << "} accuracy is ";
		 
	         accuracy = leave_one_out(data, tmp, j, false);
            cout << accuracy * 100 << "%" << endl;
            if (accuracy > bestAccuracy) {
               bestAccuracy = accuracy;
               removedFeature = j;
            }
         }
      }
	   
      currentFeatures = removeFeature(currentFeatures, removedFeature);
      cout << endl;
	   
      if (bestAccuracy > maxAccuracy) {
         maxAccuracy = bestAccuracy;
         bestFeatures = currentFeatures;
      } else {
         cout << "(Warning, accuracy has decreased! Continuing search in case of local maxima)" << endl;
      }

      cout << "Feature set {";
      displaySubset(currentFeatures, bestAccuracy);
   }

   cout << "Finished search! The best feature subset is {";
   displaySubset(bestFeatures, maxAccuracy);
}

void displaySubset(vector<int> feature, int accu) {
   for (int i = 0; i < feature.size() - 1; i++) {
      cout << feature[i] << ", ";
   }
   cout << feature[feature.size() - 1] << "} was the best, with accuracy " << acc * 100 << "%" << endl;
}

int main() {
   string filename, line;
   vector<vector<double>> dataset;
   double acc = 0.0;
   double data = 0.0;
    
   cout << "Enter the name of the file you want to test: ";
   cin >> filename;
   cout << endl;
    
   ifstream file(filename.c_str());
   if (!file.is_open()) {
      cout << "Error: unable to open file." << endl;
      return 0;
   } else {
      while (getline(file, line)) {
         stringstream lineStream(line);
         vector<double> instance;
			
         while (lineStream >> data) {
            instance.push_back(data);
         }
         dataset.push_back(instance);
      }
      file.close();
   }

   cout << endl;
   cout << "Choose an algorithm" << endl;
	cout << endl;
	cout << "1) Forward Selection" << endl;
	cout << "2) Backward Selection" << endl;
	cout << endl;

   cout << "Enter your selection: ";
   cin >> algoChoice;
   cout << endl;

   cout << "This dataset has " << dataset.at(0).size() - 1 << " features (not including the class attribute), with " << dataset.size() << " instances." << endl << endl;

   nearest_neighbour(dataset, dataset.at(0).size());
	
   cout << "Beginning search..." << endl << endl;
	
   if (choice == 1) { forwardSelection(dataset); } 
   else if (choice == 2) { backwardElim(dataset); }
}
