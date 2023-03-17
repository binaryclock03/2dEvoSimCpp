#pragma once
#include <array>
#include <map>
#include <vector>
#include "netObjects/NeuralNet.h"
#include "Population.h"
#include <string>

using namespace std;

class Simulation
{
protected:
    short gridBounds[2];
    short tick;
    short maxTick;
    unordered_map<int, int> PosId;
    unordered_map<int, int> IdPos;
    vector<NeuralNet> creatures;
    string name;
public:
    Simulation(string name);

    void simulate();
    void simulate(int steps, int generation);
    void saveState(int generation);

    void optimize();
    void buildFromPop(Population* population);

    void moveCreature(int id, int x, int y);
    void setCreaturePos(int id, int pos);

    int getCreaturePos(int id);
    int getCreatureY(int id);
    int getCreatureX(int id);

    short getSimTick() { return this->tick; };
    short getMaxSimTick() { return this->maxTick; };

    vector<int> returnSurvivors();
};