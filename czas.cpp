#include <iostream>
#include <chrono>
#include "czas.h"

using namespace std;
using namespace std::chrono;

void Czas::Start() {
    czasStart = high_resolution_clock::now();
}

void Czas::Stop() {
    czasStop = high_resolution_clock::now();
}

long Czas::czasTrwania() {

    return duration_cast<milliseconds>(Czas::czasStop - Czas::czasStart).count();
}
