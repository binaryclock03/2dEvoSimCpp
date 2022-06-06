#pragma once
#include <array>
#include <map>
#include <vector>
#include "netObjects/NeuralNet.h"
#include "Population.h"

using namespace std;

class Simulation
{
protected:
    short gridBounds[2];
    short tick;
    map<int, int> PosId;
    map<int, int> IdPos;
    vector<NeuralNet> creatures;

public:
    Simulation();

    void simulate();
    void simulate(int steps);
    void optimize();
    void buildFromPop(Population population);

    void moveCreature(int id, int x, int y);
    void setCreaturePos(int id, int pos);

    int getCreaturePos(int id);
    int getCreatureY(int id);
    int getCreatureX(int id);

    vector<int> returnSurvivornts();
};