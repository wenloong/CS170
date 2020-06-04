#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#ifndef MLSEARCH
#define MLSEARCH

char RESET[] = { 0x1b, '[', '0', ';', '3', '7', 'm', 0 };
char BOLD[] = { 0x1b, '[', '1', ';', '3', '7', 'm', 0 };
char RED[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char GREEN[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
char YELLOW[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };

class mlSearch {
   public:
      // Initialize the class with a file given by the user
      mlSearch(string filename) {
         ifstream file(filename.c_str());

         if (!file.is_open()) {
            cout << RED << "ERROR: unable to open file." << RESET << endl;
            exit(1);
         } // Exit if file is not readable

         while (getline(file, line)) {
            stringstream lineStream(line);
            vector<double> instance;

            while (lineStream >> dataInput) {
               instance.push_back(dataInput);
            }

            data.push_back(instance);
         }

         file.close();
      }

      // Normalize the data before moving on with nearest neighbour algorithm.
      // We will use min and max normalization for this instead of z-normalization
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

      // Helper function to display the subsets
      void displaySubset(vector<int> feature) {
         for (int i = 0; i < feature.size() - 1; i++) {
            cout << feature[i] << ", ";
         }
         cout << feature[feature.size() - 1] << "} was the best, with accuracy ";
      }

      // leave one out algorithm which also takes another input to detect if the algorithm
      // is forward or backwards to avoid making another function solely for forward.
      double leave_one_out(vector<vector<double>> data, bool forwardSelection, vector<int> currentFeatures ,int newFeature) {
         int numCorrect = 0;
         double temp, mDist, distance = 0;
         vector <double> testingSet;
         vector <double> nearest;
         
         for (int i = 0; i < data.size(); i++) {	
            // Let's define the min, and distance.
            testingSet = data[i]; 
            distance = 0;
            mDist = 1000000;

            for (int j = 0; j < data.size(); j++) { 
               if (j != i) { 
                  temp = 0;
            
                  for (int k = 0; k < currentFeatures.size(); k++) {
                     temp += (pow(testingSet[currentFeatures[k]] - data[j][currentFeatures[k]], 2)); // get the power
                  }
                  if (forwardSelection) {
                     temp += (pow(testingSet[newFeature] - data[j][newFeature], 2)); // Only get power if it's a forward search
                  }
                  distance = sqrt(temp);
            
                  if (distance < mDist) { 
                     mDist = distance;
                     nearest = data[j];
                  }
               }	
            }	

            // Make sure to calculate the num of correct predictions.
            if ((nearest[0] == 1 && testingSet[0] == 1) || (nearest[0] == 2 && testingSet[0] == 2)) 
               numCorrect++;
         }
         return (double)numCorrect / (double)data.size();
      }

      // nearest neighbour function to also help with our algorithm. 
      double nearest_neighbour() {
         int numFeatures = data[0].size();
         vector<int> currentFeatures;

         cout << "This data has " << data[0].size() - 1 << " features (not including the class attribute), with " << data.size() << " instances." << endl << endl;

         for (int i = 1; i < numFeatures; i++)
            currentFeatures.push_back(i);
         
         cout << "Running nearest neighbor with all " << numFeatures - 1 << " features, using \"leaving-one-out\" evaluation, I get an accuracy of ";
         double accuracy = leave_one_out(data,currentFeatures,0,false);

         return leave_one_out(data,currentFeatures,0,false);
      }

      // cari subset dengan forward selection.
      void forward_selection() {
         vector<int> currentFeatures, bestFeatures;
         double accuracy = 0, maxAccuracy = 0, globalMaxAccuracy = 0;
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

      // algorithm ini seperti forward selection. Algorithm sama tapi kita nak patuskan.
      void backward_elimination() {
         vector <int> currentFeatures;
         vector <int> bestFeatures;
         double accuracy = 0, maxAccuracy = 0, globalMaxAccuracy = 0;
         int maxIn;
            
         for (int i = 1; i < data[0].size(); i++) 
            currentFeatures.push_back(i);
         
         for (int i = 1; i < data[0].size() - 1; i++) {
            maxAccuracy = 0;
            
            for (int j = 1; j < data[0].size(); j++) { 
               if (find(currentFeatures.begin(), currentFeatures.end(), j) != currentFeatures.end()) {
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
                     maxIn = j; // penting untuk mencari accuracy sebernah. 83% - 73%. 10% jatuh.
                  }
               }
            }
            
            currentFeatures.erase(remove(currentFeatures.begin(), currentFeatures.end(), maxIn), currentFeatures.end());
            cout << endl;
            
            // Jika ini tak lapus, check ini akan jatuh
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

   private:
      vector<vector<double>> data;
      double dataInput;
      string filename, line;
};

#endif
