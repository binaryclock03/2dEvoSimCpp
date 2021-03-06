#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include <variant>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include "Neuron.h"
#include "SensorNeuron.h"
#include "InterNeuron.h"
#include "ActionNeuron.h"
#include "../Genome.h"
#include "../util.h"
#include "../functions.h"

using namespace std;

class Simulation;

class NeuralNet
{
protected:
    vector<shared_ptr<Neuron>> neurons;
    forward_list<Gene> genes;
    unordered_map<int, int> neuronIdIndexMap;
    int maxDepth;
    int id;
    int direction;
public:
    NeuralNet();
    NeuralNet(int id);

    void buildNet(Genome genome);
    void insertNeuron(int index, shared_ptr<Neuron> neuron);
    void optimize();
    void activate(Simulation *simulation);
    vector<int> checkPaths();

    forward_list<Gene> getGenes();

    void setDireciton(int dir);
    void setDireciton(int x, int y);
    int getDirection();
    int getId();
private:
    set<int> checkPath(int nodeAdr, int depth, set<int> validatedNodesInPath, set<int>& validatedNodes);
};