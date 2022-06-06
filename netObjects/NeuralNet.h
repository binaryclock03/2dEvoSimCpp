#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include "Neuron.h"
#include "../Genome.h"

using namespace std;

class Simulation;

class NeuralNet
{
protected:
    vector<Neuron> neurons;
    forward_list<Gene> genes;
    unordered_map<int, int> neuronIdIndexMap;
    int maxDepth;
public:
    NeuralNet();

    void buildNet(Genome genome);
    void addNeuronFunctions();
    void insertNeuron(int index, Neuron neuron);
    void optimize();
    void activate(Simulation *simulation);
    vector<int> checkPaths();

    forward_list<Gene> getGenes();
private:
    set<int> checkPath(int nodeAdr, int depth, set<int> validatedNodesInPath, set<int>& validatedNodes);
};