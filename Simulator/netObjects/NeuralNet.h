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
    vector<Gene> genes;
    unordered_map<int, int> neuronIdIndexMap;
    int maxDepth;
    int id;
    int direction;
public:
    NeuralNet();
    NeuralNet(int id);

    void buildNet(Genome genome);
    void insertNeuron(int index, shared_ptr<Neuron> neuron);
    void remapNeurons(vector<shared_ptr<Neuron>> neurons);
    void optimize();
    void activate(Simulation *simulation);
    unordered_set<int> checkPaths();

    vector<Gene> getGenes();

    void setDirection(int dir);
    void setDirection(int x, int y);
    int getDirection();
    int getDirectionX();
    int getDirectionY();
    int getId();
private:
    set<int> checkPath(int nodeAdr, int depth, set<int> validatedNodesInPath, set<int>& validatedNodes);
};