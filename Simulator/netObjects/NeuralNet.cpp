#include "NeuralNet.h"

NeuralNet::NeuralNet() 
{
    this->maxDepth = 1;
    this->id = 0;
    this->direction = 0;
}

NeuralNet::NeuralNet(int id)
{
    this->maxDepth = 1;
    this->id = id;
    this->direction = 0;
}

void NeuralNet::buildNet(Genome genome)
{
    unordered_set<int> usedAdr;

    for (int i = 0; i < genome.getNumberOfGenes(); i++)
    {
        Gene gene = genome.getGene(i);
        this->genes.push_front(gene);
        usedAdr.insert(gene.inAdr);
        if (gene.outAdr < 128)
            usedAdr.insert(gene.outAdr+256);
        else
            usedAdr.insert(gene.outAdr);
    }

    this->neurons.reserve(usedAdr.size());
    
    for (int i : usedAdr)
    {
        switch ((int)std::floor(i / 128))
        {
        case 0:
        {
            shared_ptr<SensorNeuron> neuron(new SensorNeuron(i, funcs.sensorFuncs[i]));
            this->neuronIdIndexMap.insert({ i, neurons.size() });
            this->neurons.push_back(neuron);
        }
        break;
        case 1:
        {
            shared_ptr<InterNeuron> neuron(new InterNeuron(i));
            this->neuronIdIndexMap.insert({ i, neurons.size() });
            this->neurons.push_back(neuron);
        }
        break;
        case 2:
        {
            shared_ptr<ActionNeuron> neuron(new ActionNeuron(i, funcs.actionFuncs[i%128]));
            this->neuronIdIndexMap.insert({ i, neurons.size() });
            this->neurons.push_back(neuron);
        }
        break;
        }
    }

    //cout << "THIS IS A STOPPING POINT" << endl;
};

void NeuralNet::optimize()
{
    int max = 1;
    for (auto neuron : this->neurons)
        if (neuron->getDepth() > max)
            max = neuron->getDepth();
    this->maxDepth = max;

    this->checkPaths();
}

void NeuralNet::activate(Simulation *simulation)
{
    for (auto neuron : this->neurons)
    {
        neuron->activate(0, this, simulation);
    }

    for (int i = 0; i < this->maxDepth; i++)
    {
        for (Gene gene : this->genes)
        {
            float strength = scale(gene.strength, 0, 65535, -4.0f, 4.0f);
            float value = this->neurons[this->neuronIdIndexMap[gene.inAdr]]->getValue();
            value = value * strength;
            if (gene.outAdr > 127)
                this->neurons[this->neuronIdIndexMap[gene.outAdr+128]]->addIncoming(value);
            else
                this->neurons[this->neuronIdIndexMap[gene.outAdr]]->addIncoming(value);
        }

        for (auto neuron : this->neurons)
        {
            neuron->activate(1, this, simulation);
        }
    }

    for (auto neuron : this->neurons)
    {
        neuron->activate(2, this, simulation);
    }

    for (auto neuron : this->neurons)
    {
        neuron->activate(3, this, simulation);
    }
};

void NeuralNet::insertNeuron(int index, shared_ptr<Neuron> neuron)
{
    this->neuronIdIndexMap.insert({index, neurons.size()});
    this->neurons.push_back(neuron);
}

forward_list<Gene> NeuralNet::getGenes()
{
    return this->genes;
}

void NeuralNet::setDirection(int dir)
{
    this->direction = clamp(dir, 0, 8);
}

void NeuralNet::setDirection(int x, int y)
{
    if (x == 0 && y == 0)
        this->direction = 0;

    else if (x == 0 && y > 0)
        this->direction = 1;

    else if (x > 0 && y > 0)
        this->direction = 2;

    else if (x > 0 && y == 0)
        this->direction = 3;

    else if (x > 0 && y < 0)
        this->direction = 4;

    else if (x == 0 && y < 0)
        this->direction = 5;

    else if (x < 0 && y < 0)
        this->direction = 6;

    else if (x < 0 && y == 0)
        this->direction = 7;

    else if (x < 0 && y > 0)
        this->direction = 8;
}

int NeuralNet::getDirection()
{
    return this->direction;
}

int NeuralNet::getDirectionX()
{
    if (this->direction == 2 || this->direction == 3 || this->direction == 4) { return 1; }
    else if (this->direction == 6 || this->direction == 7 || this->direction == 8) { return -1; }
    else { return 0; }
}

int NeuralNet::getDirectionY()
{
    if (this->direction == 1 || this->direction == 2 || this->direction == 8) { return 1; }
    else if (this->direction == 4 || this->direction == 5 || this->direction == 6) { return -1; }
    else { return 0; }
}

int NeuralNet::getId()
{
    return this->id;
}

set<int> NeuralNet::checkPath(int nodeAdr, int depth, set <int> validatedNodesInPath, set<int>& validatedNodes) {
    auto& neuron = this->neurons[this->neuronIdIndexMap[nodeAdr]];

    if (depth > 1000) {
        set<int> emptySet;
        return emptySet;
    }

    //Checks neuron depth and assigns it a new depth if needed
    if (neuron->getDepth() == 0) {
        neuron->setDepth(depth);
    } else if (depth < neuron->getDepth()){
        neuron->setDepth(depth);
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
                if(this->neurons[this->neuronIdIndexMap[gene.outAdr]]->getDepth() == 0 || this->neurons[this->neuronIdIndexMap[gene.outAdr]]->getDepth() < neuron->getDepth()) {
                    neurons[this->neuronIdIndexMap[gene.outAdr]]->setDepth(neuron->getDepth()+1);
                }
            } else if (validatedNodes.count(gene.outAdr) < 0)
            {
                nodesBelow.insert(gene.outAdr);
            } else if ((gene.inAdr != gene.outAdr) && //Checks if the next inter neuron is not its self or lower 
            (this->neurons[this->neuronIdIndexMap[gene.outAdr]]->getDepth() == 0 || this->neurons[this->neuronIdIndexMap[gene.outAdr]]->getDepth() > neuron->getDepth()))
            {
                nodesBelow.merge(this->checkPath(gene.outAdr,depth+1,validatedNodesInPath,validatedNodes)); //Check path of the next node
            }
            if (!nodesBelow.empty()) //Checks if theres anything to add to to_return. This is what will stop a branch from being recorded if there is a deadend.
            {
                nodesBelow.insert(nodeAdr);
                validatedNodesInPath.merge(nodesBelow);
            }

        } else if (this->neurons[this->neuronIdIndexMap[gene.outAdr]]->getDepth() != 0 && gene.inAdr == nodeAdr && this->neurons[this->neuronIdIndexMap[gene.outAdr]]->getDepth() < neuron->getDepth())
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