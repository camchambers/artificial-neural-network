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

// Reads a file to create a training set
void TrainingSet::read(string fileName)
{
    cout << "Attempting to read traning set from file \"" << fileName << "\"" << endl
         << endl;
}