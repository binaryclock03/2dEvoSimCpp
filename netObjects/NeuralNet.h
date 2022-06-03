#pragma once
#include <unordered_map>
#include <unordered_set>
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
    unordered_set<int> checkPaths();

    forward_list<Gene> getGenes();
private:
    unordered_set<int> checkPath(int nodeAdr, int depth, unordered_set<int> validatedNodesInPath, unordered_set<int> validatedNodes);
};