#ifndef ALGORITHM_H
#define ALGORITHM_H

class Algorithm {
   public:
      
}

#endif




int main() {
   string filename, line;
   double accuracy = 0, temp = 0;
   int algoChoice;
   vector<vector<double>> data;

   cout << "Enter the file name you would like to test: ";
	cin >> fileName;
   cout << endl;

   fin.open(fileName.c_str());

	if (!fin) {
		cout << "ERROR: Invalid file" << endl;
		exit(1); 
	}

   while (getline(file, line)) {
      vector<double> inst;
      stringstream ss(line);

      while(ss >> temp) {
         inst.push_back(temp);
      }

      data.push_back(inst);
   }

   file.close();

   cout << endl;
   cout << "Choose an algorithm" << endl;
	cout << endl;
	cout << "1) Forward Selection" << endl;
	cout << "2) Backward Selection" << endl;
	cout << endl;

   cout << "Enter your selection: ";
   cin >> algoChoice;
   cout << endl;

   normalizeData(data);
}

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

double nearest_neighbour(vector<vector>double>> data, vector<int> featureSubset, int index, int numInstance) {
   int min_index = 0;
   double temp_distance = 0, min_distance = 1000000;

   for (int i = 0; i < numInstance; i++) {
      temp_distance = 0;

      if (i != index) {
         for (int j = 0; j < featureSubset.size(); j++) {
            temp_distance += pow((data.at(i).at()))
         }
      }
   }

}
