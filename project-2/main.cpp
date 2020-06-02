#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

double leaveOneOut(vector< vector<double> > data,vector<int> currFeatures,int newFeature,bool isForward) {
	int numCorrect = 0; // number of correct classifications
	double tmp, accuracy, min_dist, dist = 0;
	vector <double> testingSet;
	vector <double> nearest; // nearest neighbor (closest point in training set)
	
	for (int i = 0; i < data.size(); i++) {	
		testingSet = data.at(i); 
		min_dist = 1000000;
		dist = 0;

		for (int j = 0; j < data.size(); j++) { 
			if (j != i) { 
				tmp = 0;
				for (int k = 0; k < currFeatures.size(); k++)  
					tmp += (pow(testingSet.at(currFeatures.at(k)) - data.at(j).at(currFeatures.at(k)), 2));
				if (isForward)
					tmp += (pow(testingSet.at(newFeature) - data.at(j).at(newFeature), 2));
				dist = sqrt(tmp);
				if (dist < min_dist) { 
					min_dist = dist;
					nearest = data.at(j);
				}
			}	
		}	
		
		// if predicted/actual classifications are the same, increment numCorrect
		if (nearest.at(0) == 1 && testingSet.at(0) == 1) 
			++numCorrect;
		else if (nearest.at(0) == 2 && testingSet.at(0) == 2)
			++numCorrect;
	}
	
	accuracy = (double)numCorrect / (double)data.size();
	return accuracy;
}

void NN(vector< vector<double> > data, int numFeatures) {
	vector<int> currFeatures;
	for (int i = 1; i < numFeatures; i++)
		currFeatures.push_back(i);
	
	double accuracy = leaveOneOut(data,currFeatures,0,false);
				
	cout << "Running nearest neighbor with all " << numFeatures-1 << " features, using \"leaving-one-out\" evaluation, I get an accuracy of " << accuracy * 100 << "%" << endl << endl;
				
	return;
}

void forwardSelection(vector< vector<double> > data) {
	vector<int> currFeatures; // current set of features being tested
	vector<int> bestFeatures; // set of features with highest accuracy 
	double accuracy = 0; 
	double bestAccuracy = 0; // highest accuracy to a certain point
	double maxAccuracy = 0; // highest accuracy overall
	int addedFeature;
	
	for (int i = 1; i < data.at(0).size(); i++) {
		bestAccuracy = 0;
		for (int j = 1; j < data.at(0).size(); j++) { 
			if (std::find(currFeatures.begin(), currFeatures.end(), j) == currFeatures.end()) {
				accuracy = leaveOneOut(data,currFeatures, j, true);
				
				cout << "\tUsing feature(s) {";
				for (int k = 0; k < currFeatures.size(); k++) 
					cout << currFeatures.at(k) << ",";
				cout << j << "} accuracy is ";

				cout << accuracy * 100 << "%" << endl;
				if (accuracy > bestAccuracy) {
					addedFeature = j;
					bestAccuracy = accuracy;
				}
			}
		}
		currFeatures.push_back(addedFeature);
		cout << endl;
		if (bestAccuracy > maxAccuracy) {
			maxAccuracy = bestAccuracy;
			bestFeatures = currFeatures;
		}
		else {
			cout << "(Warning, accuracy has decreased! Continuing search in case of local maxima)" << endl;
		}
		cout << "Feature set {";
		for (int k = 0; k < currFeatures.size() - 1; k++)
			cout << currFeatures.at(k) << ",";
		cout << currFeatures.at(currFeatures.size() - 1);
		cout <<"} was best, accuracy is ";
		cout << bestAccuracy * 100 << "%" << endl << endl;
	}
	
	cout << "Finished search!! The best feature subset is {";
	for (int k = 0; k < bestFeatures.size() - 1; k++)
		cout << bestFeatures.at(k) << ",";
	cout << bestFeatures.at(bestFeatures.size() - 1);
	cout << "}, which has an accuracy of " << maxAccuracy * 100 << "%" << endl;
	
	return;
}

// helper function for backward elimination (removes feature from vector)
vector <int> removeFeature(vector<int> currFeatures, int removedFeature) {
	for (int i = 0; i < currFeatures.size(); i++) {
		if (currFeatures.at(i) == removedFeature) {
			currFeatures.erase(currFeatures.begin() + i);
			return currFeatures;
		}
	}
	return currFeatures;
}

void backwardElim(vector< vector<double> > data) {
	vector <int> currFeatures;
	vector <int> bestFeatures;
	double accuracy = 0;
	double bestAccuracy = 0;
	double maxAccuracy = 0;
	int removedFeature;
		
	for (int i = 1; i < data.at(0).size(); i++) 
		currFeatures.push_back(i);
	
	for (int i = 1; i < data.at(0).size() - 1; i++) {
		bestAccuracy = 0;
		for (int j = 1; j < data.at(0).size(); j++) { 
			if (std::find(currFeatures.begin(), currFeatures.end(), j) != currFeatures.end()) {
				vector <int> tmp = removeFeature(currFeatures, j);
				cout << "\tUsing feature(s) {";
				for (int k = 0; k < tmp.size() - 1; k++)
					cout << tmp.at(k) << ",";
				cout << tmp.at(tmp.size() - 1) << "} accuracy is ";

				accuracy = leaveOneOut(data, tmp, j, false);
				cout << accuracy * 100 << "%" << endl;
				if (accuracy > bestAccuracy) {
					bestAccuracy = accuracy;
					removedFeature = j;
				}
			}
		}
		currFeatures = removeFeature(currFeatures, removedFeature);
		cout << endl;
		if (bestAccuracy > maxAccuracy) {
			maxAccuracy = bestAccuracy;
			bestFeatures = currFeatures;
		}
		else
			cout << "(Warning, accuracy has decreased! Continuing search in case of local maxima)" << endl;
		cout << "Feature set {";
		for (int k = 0; k < currFeatures.size() - 1; k++)
			cout << currFeatures.at(k) << ",";
		cout << currFeatures.at(currFeatures.size() - 1);
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
	}
	else {
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
	
	cout << endl;
	cout << "This dataset has " << dataset.at(0).size() - 1 << " features (not including the class attribute), with " << dataset.size() << " instances." << endl << endl;

	NN(dataset, dataset.at(0).size());
	
	cout << "Beginning search..." << endl << endl;
	
	if (choice == 1) {
		forwardSelection(dataset);
	}
	else if (choice == 2) {
		backwardElim(dataset);
	}
	else if (choice == 3) {
	//	mySearch(dataset);
	}
	return 0;
}
