#pragma once
#include <array>
#include <unordered_map>
#include <vector>
#include "netObjects/NeuralNet.h"

using namespace std;

class Simulation
{
protected:
    //typedef array<int, 2> pos;

    short gridBounds[2] = {128,128};
    short tick = 0;
    //unordered_map<pos, int> positions;
    unordered_map<int, int> creatureIdIndexMap;
    vector<NeuralNet> creatures;
public:
    Simulation();
    void simulate();
    void simulate(int steps);
    void optimize();
};