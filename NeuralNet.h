#pragma once
#include <unordered_map>
#include "Neuron.h"
#include "Genome.h"

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
    void checkPaths();

    forward_list<Gene> getGenes();
private:
    void checkPath();
};