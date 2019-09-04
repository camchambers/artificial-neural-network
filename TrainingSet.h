#pragma once
#include <vector>
using namespace std;

class TrainingSet
{
public:
    void read(string filename);
    void scale();

private:
    vector<string> classLabels;
    vector<vector<double>> trainingData;
};