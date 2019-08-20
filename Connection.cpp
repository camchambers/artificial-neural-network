#include "Connection.h"
using namespace std;
#include <iostream>

Connection::Connection()
{
    weight = (double)rand() / RAND_MAX * 2.0 - 1.0;
}

void Connection::print()
{
    cout << weight;
}