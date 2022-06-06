#pragma once
#include <array>
#include <unordered_map>
#include <vector>
#include "netObjects/NeuralNet.h"
#include "Population.h"

using namespace std;

class Simulation
{
protected:
    short gridBounds[2] = {128,128};
    short tick = 0;
    unordered_map<int, int> positions;
    vector<NeuralNet> creatures;
public:
    Simulation();
    void simulate();
    void simulate(int steps);
    void optimize();
    void buildFromPop(Population population);
};