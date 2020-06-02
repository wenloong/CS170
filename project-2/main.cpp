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
void normalizeData(vector<vector<double>> dataset, int numInstance, int numFeatures) {

	cout << "This dataset has " << numFeatures - 1 << " features (not including the class attribute), with "
			<< numInstances << " instances." << endl;

	cout << endl;
	cout << "Please wait while I normalize the data... ";

	double sum;
	double varianceNum;
	double variance;
	double mean[numFeatures];
	double std[numFeatures];
	
	// Calculating the mean for each column (feature)
	for (int j = 1; j < numFeatures; ++j){
		sum = 0;

		for (int i = 0; i < numInstances; i++){
			sum += dataset[i][j];

		}

		mean[j] = sum / numInstances;
	}

	// Calculating the standard deviation for each column (feature)
	for (int j = 1; j < numFeatures; ++j){
		varianceNum = 0;

		for (int i = 0; i < numInstances; i++){
			varianceNum += pow(dataset[i][j] - mean[j], 2);

		}

		variance = varianceNum / numInstances;
		std[j] = sqrt(variance);
	}

	// Normalizing each data point
	for (int i = 0; i < numInstances; i++){
		for (int j = 1; j < numFeatures; j++){
			dataset[i][j] = (dataset[i][j] - mean[j]) / std[j];
		}
	}

	cout << "Done!" << endl;
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
			if (std::find(currentFeatures.begin(), currentFeatures.end(), j) != currentFeatures.end()) {
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
		}
		else
			cout << "(Warning, accuracy has decreased! Continuing search in case of local maxima)" << endl;
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

int main() {
    
    string filename, line;
    vector< vector<double> > dataset;
    double acc = 0.0;
    double data = 0.0;
    
    cout << "Welcome to Sabrina Chen's Feature Selection Algorithm." << endl << "Type in the name of the file to test: ";
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

	cout << "Type the number of the algorithm you want to run. " << endl;
	cout << "\t1) Forward Selection" << endl;
	cout << "\t2) Backward Elimination" << endl;
	cout << "\t3) Sabrina's Special Algorithm" << endl;
	int choice = 0;
	while (choice < 1 || choice > 3) {
		cin >> choice;
	}

	normalizeData(dataset);
	cout << endl;
	cout << "This dataset has " << dataset.at(0).size() - 1 << " features (not including the class attribute), with " << dataset.size() << " instances." << endl << endl;

	nearest_neighbour(dataset, dataset.at(0).size());
	
	cout << "Beginning search..." << endl << endl;
	
	if (choice == 1) {
		forwardSelection(dataset);
	} else if (choice == 2) {
		backwardElim(dataset);
	}
	return 0;
}
