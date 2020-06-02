#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

const int MAX_INSTANCES = 2048;
const int MAX_FEATURES = 64;

int main () {
	double dataArr[MAX_INSTANCES][MAX_FEATURES];

   int algoChoice;
	string fileName;
	ifstream fin;

	int numFeatures = 0;
	int numInstances = 0;
	double accuracy;
	string line;
	double word;
	int input;
   

	cout << "Enter the file name you would like to test: ";
	cin >> fileName;

	fin.open(fileName.c_str());

	if (!fin) {
		cout << "ERROR: Invalid file" << endl;
		exit(1); 
	}

   cout << endl;
   cout << "Choose an algorithm" << endl;
	cout << endl;
	cout << "1) Forward Selection" << endl;
	cout << "2) Backward Selection" << endl;
	cout << endl;

   cin >> algoChoice;

   // load data file into our program
	// also, count the number of instances and features
	while (getline(fin, line)){
		numFeatures = 0;
		stringstream s(line);

		while(s >> word){
			dataArray[numInstances][numFeatures] = word;
			numFeatures++;
		}

		numInstances++;
	}

   // Normalize the data first.
	normalizeData(dataArray, numInstances, numFeatures);

   vector<int> allFeaturesSubset;
   vector<int> solution;

   for (int j =1; j < numFeatures; j++) {
		allFeaturesSubset.push_back(j);
	}

	accuracy = leaveOneOut(dataArray, allFeaturesSubset, numInstances);
	cout << endl;
	cout << "Running nearest neighbor with all " << numFeatures - 1 
			<< " features, using \"leave-one-out\" evaluation, I get an accuracy of " << accuracy << "%" << endl;   

   if (algoChoice == 1) {
      solution = forwards(dataArr, numInstances, numFeatures);
   } else if (algoChoice == 2) {
      solution = backwards(dataArr, numInstances, numFeatures);
   } else {
      cout << "Error: Invalid Choice" << endl;
      exit(1);
   }

   cout << "Search complete. Here is the best feature subset: ";
   displaySubset(solution);
   cout << endl << "This has an accuracy of " << leaveOneOut(dataArr, solution, numInstances) << "%" << endl << endl;

	return 0;
}


/*
   Accepts: vector<int>
   Description: Displays feature subsets
*/
void displaySubset (vector<int> subset) {
	cout << "{";
   for (int i = 0; i < subset.size(); i++) {
      cout << subset.at(i);

      if (i != subset.size() - 1)
         cout << ", ";
   }
   cout << "}";
}

/*
   Accepts: double, int int
   Description: Required function to normalize.
   
   Normalized Data:  X = ( X-MEAN ) / STANDARD DEVIATION
*/
void normalizeData (double (&dataset)[MAX_INSTANCES][MAX_FEATURES], int numInstances, int numFeatures) {
   cout << "-- Normalizing Data --" << endl;

   vector<double> fMin;
   vector<double> fMax;

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

double nearestNeighbor (double dataset[MAX_INSTANCES][MAX_FEATURES], int instIndex, vector<int> featureSubset, int numInstances) {
//  This function finds the nearest neighbor of an instance given a featureSubset
//	returns: classification of nearest neighbor

	int nearestIndex = 0;
	double tempDistance = 0;
	double nearestDistance = numeric_limits<double>::max();

// loop through rows and to find row with smallest distance
// nearest distance is the MINIMUM of distances (given the feature subset)
	for (int i = 0; i < numInstances; i ++){

		tempDistance = 0;

		if (i != instIndex){

			for (int j = 0; j < featureSubset.size(); j++){
				tempDistance += pow((dataset[i][featureSubset.at(j)] - dataset[instIndex][featureSubset.at(j)]), 2);
			}

			tempDistance = sqrt(tempDistance);

			if (tempDistance < nearestDistance){
				nearestIndex = i;
				nearestDistance = tempDistance;
			}
		}
	}

	return dataset[nearestIndex][0];
}

double leaveOneOut (double dataset[MAX_INSTANCES][MAX_FEATURES], vector<int> featureSubset, int numInstances){
// This function is our leave one out algorithm 
// returns: accuracy

	int numCorrectPredict = 0;

	for (int i = 0; i < numInstances; i++) {

		double prediction = nearestNeighbor(dataset, i, featureSubset, numInstances);

		if (dataset[i][0] == prediction){
			numCorrectPredict++;
		}
	}

//	cout << numCorrectPredict<< endl;
//	cout << (double(numCorrectPredict)/numInstances * 100) << endl;
	return (double(numCorrectPredict)/numInstances * 100);
}

vector<int> forwards (double dataset[MAX_INSTANCES][MAX_FEATURES], int numInstances, int numFeatures){
// This function performs a forwardSelection greedy search
// returns: nothing (prints subset with greatest accuracy)
	cout << endl;
	cout << "Beginning search." << endl;

	// In forwards selection, we initialize to empty set
	vector<int> selectedSubset;
	vector<int> solution;

	double tempAccuracy;
	double maxAccuracy;
	double maxMaxAccuracy = 0;
	bool foundSolutionSubset;

	int maxIndex;

	for (int i = 1; i < numFeatures; i++){
		foundSolutionSubset = false;
		maxAccuracy = 0;
		maxIndex = 0;
		cout << endl;
		for (int j = 1; j < numFeatures; j++){
			//cout << endl;
			if (!(find(selectedSubset.begin(), selectedSubset.end(), j) != selectedSubset.end())){
				vector<int> temp = selectedSubset;
				temp.push_back(j);

				tempAccuracy = leaveOneOut(dataset, temp, numInstances);

				// print statement
				cout << "		Using feature(s) ";
				displaySubset(temp);
				cout << " accuracy is " << tempAccuracy << "%" << endl;

				// max accuracy amongst particular set of subsets
				if (tempAccuracy > maxAccuracy){
					maxAccuracy = tempAccuracy;
					maxIndex = j;

					// max accuracy of ALL subsets
					if (tempAccuracy > maxMaxAccuracy){
						maxMaxAccuracy = tempAccuracy;
						foundSolutionSubset = true;
					}
				}

			}

		}
		cout << endl;
		selectedSubset.push_back(maxIndex);

		if (foundSolutionSubset){
			solution.push_back(maxIndex);
		}
		else{
			if (selectedSubset.size() != numFeatures - 1){
			cout << "(Warning: Accuracy has decreased! Continuing search in case of local maxima)" << endl;
			}
		}


		if (selectedSubset.size() != numFeatures - 1){
			cout << "Feature set ";
			displaySubset(selectedSubset);
			cout << " was best, accuracy is, " << maxAccuracy << "%" << endl;
		}
	}

	// cout << endl;
	// cout << "Finished search!! The best feature subset is ";
	// displaySubset(solution);
	// cout << ", which has an accuracy of " << maxMaxAccuracy << "%" << endl;
	// cout << endl;
	return solution;
}

vector<int> backwards (double dataset[MAX_INSTANCES][MAX_FEATURES], int numInstances, int numFeatures){
// This function performs a forwardSelection greedy search
// returns: nothing (prints subset with greatest accuracy)

	// in backwards selection, we initialize to set of all features
	vector<int> selectedSubset;
	for (int j =1; j < numFeatures; j++) {
		selectedSubset.push_back(j);
	}

	vector<int> solution = selectedSubset;

	double tempAccuracy;
	double maxAccuracy;
	double maxMaxAccuracy = leaveOneOut(dataset, selectedSubset, numInstances);
	bool foundSolutionSubset;
	int maxIndex;

	cout << "		Using feature(s) ";
	displaySubset(selectedSubset);
	cout << " accuracy is " << maxMaxAccuracy << "%" << endl;

	cout << endl;
	cout << "Beginning search." << endl;
	for (int i = 1; i < numFeatures - 1; i++){
		foundSolutionSubset = false;
		maxAccuracy = 0;
		maxIndex = 0;
		cout << endl;
		for (int j = 1; j < numFeatures; j++){
			//cout << endl;
			if ((find(selectedSubset.begin(), selectedSubset.end(), j) != selectedSubset.end())){
				vector<int> temp = selectedSubset;
				temp.erase(remove(temp.begin(), temp.end(), j), temp.end());

				tempAccuracy = leaveOneOut(dataset, temp, numInstances);

				// print statement
				cout << "		Using feature(s) ";
				displaySubset(temp);
				cout << " accuracy is " << tempAccuracy << "%" << endl;

				// max accuracy amongst particular set of subsets
				if (tempAccuracy > maxAccuracy){
					maxAccuracy = tempAccuracy;
					maxIndex = j;

					// max accuracy of ALL subsets
					if (tempAccuracy > maxMaxAccuracy){
						maxMaxAccuracy = tempAccuracy;
						foundSolutionSubset = true;
					}
				}

			}

		}
		cout << endl;
		selectedSubset.erase(remove(selectedSubset.begin(), selectedSubset.end(), maxIndex), selectedSubset.end());

		if (foundSolutionSubset){
			solution.erase(remove(solution.begin(), solution.end(), maxIndex), solution.end());
		}
		else{
			if (selectedSubset.size() != 1){
			cout << "(Warning: Accuracy has decreased! Continuing search in case of local maxima)" << endl;
			}
		}

		cout << "Feature set ";
		displaySubset(selectedSubset);
		cout << " was best, accuracy is, " << maxAccuracy << "%" << endl;
		
	}


	return solution;
}

