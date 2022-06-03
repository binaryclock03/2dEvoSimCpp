#include "NeuralNet.h"
#include "SensorNeuron.h"
#include "InterNeuron.h"
#include "ActionNeuron.h"
#include <unordered_set>

NeuralNet::NeuralNet() {}

void NeuralNet::buildNet(Genome genome)
{
    unordered_set<int> usedAdr;

    for (int i = 0; i < genome.getNumberOfGenes(); i++)
    {
        Gene gene = genome.genes[i];
        this->genes.push_front(gene);
        usedAdr.insert(gene.inAdr);
        usedAdr.insert(gene.outAdr);
    }
    
    for (int i : usedAdr)
    {
        switch (i%128)
        {
        case 0:
            this->neurons.insert({i, SensorNeuron(i)});
        case 1:
            this->neurons.insert({i, InterNeuron(i)});
        case 2:
            this->neurons.insert({i, ActionNeuron(i)});
        }
    }
};

void NeuralNet::insertNeuron(int index, Neuron neuron)
{
    this->neurons.insert({index, neuron});
}

forward_list<Gene> NeuralNet::getGenes()
{
    return this->genes;
}