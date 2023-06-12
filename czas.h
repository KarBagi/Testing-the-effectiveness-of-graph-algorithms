#include <iostream>
#include <chrono>

#ifndef CZAS_H
#define CZAS_H

using namespace std;
using namespace std::chrono;

class Czas
{
public:
    high_resolution_clock::time_point czasStart;
    high_resolution_clock::time_point czasStop;

    void Start();

    void Stop();

    long czasTrwania();
};


#endif
