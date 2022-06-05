#pragma once
#include <unordered_map>
#include <set>
#include <vector>
#include "Neuron.h"
#include "../Genome.h"

using namespace std;

class NeuralNet
{
protected:
    unordered_map<int, Neuron> neurons;
    forward_list<Gene> genes;
    int maxDepth;
public:
    NeuralNet();

    void buildNet(Genome genome);
    void insertNeuron(int index, Neuron neuron);
    void optimize();
    void activate();
    vector<int> checkPaths();

    forward_list<Gene> getGenes();
private:
    set<int> checkPath(int nodeAdr, int depth, set<int> validatedNodesInPath, set<int>& validatedNodes);
};