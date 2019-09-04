#pragma once
#include <vector>
using namespace std;

class TrainingSet
{
public:
    void read(string filename);
    int recordCount();
    vector<double> getRecord(int index);
    void scale();

private:
    vector<vector<double>> trainingData;
    vector<int> classLabels;
    int readIndex = 0;
    int numberOfRecords;
};