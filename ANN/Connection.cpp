#include "Connection.h"
#include <iostream>
#include <random>

using namespace std;

// Static random number generator for initializing connection weights
static random_device rd; // hardware entropy
static mt19937 gen(rd()); // random number engine
static uniform_real_distribution<double> dis(-1.0, 1.0); // distribution

Connection::Connection()
{
    weight = dis(gen);
}

void Connection::print() const
{
    cout << weight;
}