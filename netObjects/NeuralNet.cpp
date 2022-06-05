#include "NeuralNet.h"
#include "SensorNeuron.h"
#include "InterNeuron.h"
#include "ActionNeuron.h"
#include "../util.h"
#include <unordered_set>
#include <set>
#include <vector>
#include <algorithm>

NeuralNet::NeuralNet() {}

void NeuralNet::buildNet(Genome genome)
{
    unordered_set<int> usedAdr;

    for (int i = 0; i < genome.getNumberOfGenes(); i++)
    {
        Gene gene = genome.getGene(i);
        this->genes.push_front(gene);
        usedAdr.insert(gene.inAdr);
        usedAdr.insert(gene.outAdr);
    }

    neurons.reserve(usedAdr.size());
    
    for (int i : usedAdr)
    {
        switch (i%128)
        {
        case 0:
            this->neuronIdIndexMap.insert({i, neurons.size()});
            this->neurons.push_back(SensorNeuron(i));
            break;
        case 1:
            this->neuronIdIndexMap.insert({i, neurons.size()});
            this->neurons.push_back(InterNeuron(i));
            break;
        case 2:
            this->neuronIdIndexMap.insert({i, neurons.size()});
            this->neurons.push_back(ActionNeuron(i));
            break;
        }
    }
};

void NeuralNet::optimize()
{
    //LMAO KING DO SOMETHING
}

void NeuralNet::activate()
{
    for (Neuron& neuron : neurons)
    {
        neuron.activate(0, this);
    }

    for (Gene& gene : this->genes)
    {
        float strength = scale(gene.strength, 0, 65535, -4.0f, 4.0f);
        float value = neurons[this->neuronIdIndexMap[gene.inAdr]].getValue();
        value = value * strength;
        neurons[this->neuronIdIndexMap[gene.outAdr]].setValue(value);
    }

    for (Neuron& neuron : neurons)
    {
        neuron.activate(1, this);
    }

    for (Neuron& neuron : neurons)
    {
        neuron.activate(2, this);
    };
};

void NeuralNet::insertNeuron(int index, Neuron neuron)
{
    this->neuronIdIndexMap.insert({index, neurons.size()});
    this->neurons.push_back(neuron);
}

forward_list<Gene> NeuralNet::getGenes()
{
    return this->genes;
}

set<int> NeuralNet::checkPath(int nodeAdr, int depth, set <int> validatedNodesInPath, set<int>& validatedNodes) {
    Neuron& neuron = this->neurons[nodeAdr];

    if (depth > 1000) {
        set<int> emptySet;
        return emptySet;
    }

    //Checks neuron depth and assigns it a new depth if needed
    if (neuron.getDepth() == 0) {
        neuron.setDepth(depth);
    } else if (depth < neuron.getDepth()){
        neuron.setDepth(depth);
    }

    bool deadEnd = true; //assume node is a dead end
    //Loop through genes
    for (Gene gene : this->genes) {
        set<int> nodesBelow;

        if (gene.inAdr == nodeAdr) { //If current node
            deadEnd = false; //Since the node has the start of a connection is probably not a dead end

            if (gene.outAdr < 128) { //If next node is an action node
                nodesBelow.insert(gene.outAdr+256);

                //Checks if this action neuron needs to have its depth assigned
                if(this->neurons[gene.outAdr].getDepth() == 0 || this->neurons[gene.outAdr].getDepth() < neuron.getDepth()) {
                    neurons[gene.outAdr].setDepth(neuron.getDepth()+1);
                }
            } else if (validatedNodes.count(gene.outAdr) < 0)
            {
                nodesBelow.insert(gene.outAdr);
            } else if ((gene.inAdr != gene.outAdr) && //Checks if the next inter neuron is not its self or lower 
            (this->neurons[gene.outAdr].getDepth() == 0 || this->neurons[gene.outAdr].getDepth() > neuron.getDepth()))
            {
                nodesBelow.merge(this->checkPath(gene.outAdr,depth+1,validatedNodesInPath,validatedNodes)); //Check path of the next node
            }
            if (!nodesBelow.empty()) //Checks if theres anything to add to to_return. This is what will stop a branch from being recorded if there is a deadend.
            {
                nodesBelow.insert(nodeAdr);
                validatedNodesInPath.merge(nodesBelow);
            }

        } else if (this->neurons[gene.outAdr].getDepth() != 0 && gene.inAdr == nodeAdr && this->neurons[gene.outAdr].getDepth() < neuron.getDepth())
        {
            validatedNodesInPath.insert(nodeAdr);
        }
    }
    if (deadEnd) {
        set<int> emptySet;
        emptySet.clear();
        return emptySet;
    } else {
        return validatedNodesInPath;
    }
}


vector<int> NeuralNet::checkPaths() {
    set <int> activeAdrs;
    set <int> emptySet;
    unordered_set <int> checkedInAdrs;

    emptySet.clear();

      for (Gene gene : this->genes) 
    {
      if (gene.inAdr < 128 && checkedInAdrs.count(gene.inAdr) < 1 ) {
          checkedInAdrs.insert(gene.inAdr);
          activeAdrs.merge(this->checkPath(gene.inAdr,0,emptySet,activeAdrs));
      }  
    }
    std::vector<int> activeAdrsVec;
    activeAdrsVec.reserve(activeAdrs.size());

    for (int adr : activeAdrs) {
        activeAdrsVec.push_back(adr);
    }
    return activeAdrsVec;
}