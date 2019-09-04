#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "TrainingSet.h"

using namespace std;

// Return the number of records read by the training set
int TrainingSet::recordCount()
{
    return this->numberOfRecords;
}

vector<double> TrainingSet::getRecord(int index)
{
    if (index > this->numberOfRecords)
    {
        cout << "Error: invalid training set index";
        exit(1);
    }
    return this->trainingData[readIndex];
}
