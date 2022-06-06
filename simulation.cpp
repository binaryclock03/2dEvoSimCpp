#include "Simulation.h"
#include "Population.h"
#include "util.h"

Simulation::Simulation() 
{
    this->gridBounds[0] = 128;
    this->gridBounds[1] = 128;
    this->tick = 0;
};

void Simulation::simulate()
{
    for (NeuralNet& creature : this->creatures)
    {
        creature.activate(this);
    }
}

void Simulation::simulate(int steps)
{
    for (int i = 0; i<steps; i++)
        this->simulate();
}

void Simulation::optimize()
{
    for (NeuralNet& creature : this->creatures)
    {
        creature.optimize();
    }
}

void Simulation::buildFromPop(Population population)
{
    for (int i = 0; i < population.getNumberOfGenomes(); i++)
    {
        int pos = randInt(0, this->gridBounds[0]*this->gridBounds[1]);
        this->PosId.insert({pos, i});
        this->IdPos.insert({i, pos});

        NeuralNet creature = NeuralNet();
        creature.buildNet(population.getGenome(i));
        creature.addNeuronFunctions();
        this->creatures.push_back(creature);
    }
}

vector<int> Simulation::returnSurvivors()
{
    vector<int> survivors;
    for (int i = 0; i < creatures.size(); i++)
    {
        if (this->getCreatureY(i) > ((int) this->gridBounds[1]/2))
            survivors.push_back(i);
    }
    return survivors;
}

int Simulation::getCreaturePos(int id)
{
    return this->IdPos[id];
}

int Simulation::getCreatureX(int id)
{
    return (int) this->getCreaturePos(id) / this->gridBounds[0];
}

int Simulation::getCreatureY(int id)
{
    return (int) this->getCreaturePos(id) % this->gridBounds[1];
}

void Simulation::setCreaturePos(int id, int pos)
{
    int beforePos = this->IdPos[id];
    this->PosId.erase(beforePos);
    this->PosId.insert({pos, id});
    this->IdPos[id] = pos;
}

void Simulation::moveCreature(int id, int x, int y)
{
    int pos = this->getCreaturePos(id);
    if(!(this->getCreatureX(id) == (this->gridBounds[0]-1) && x > 0))
        pos += x;
    if(!(this->getCreatureY(id) == (this->gridBounds[1]-1) && y > 0))
        pos += y*this->gridBounds[0];
    if(!(this->getCreatureX(id) == 0 && x < 0))
        pos += x;
    if(!(this->getCreatureY(id) == 0 && y < 0))
        pos += y*this->gridBounds[0];
    this->setCreaturePos(id, pos);
}
