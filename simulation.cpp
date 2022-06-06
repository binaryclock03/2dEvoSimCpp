#include "Simulation.h"
#include "Population.h"
#include "util.h"

Simulation::Simulation() {};

void Simulation::simulate()
{
    for (NeuralNet creature : this->creatures)
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

}

void Simulation::buildFromPop(Population population)
{
    for (int i = 0; i < population.getNumberOfGenomes(); i++)
    {
        this->positions.insert({randInt(0, this->gridBounds[0]*this->gridBounds[1]), this->creatures.size()});

        NeuralNet creature = NeuralNet();
        creature.buildNet(population.getGenome(i));
        this->creatures.push_back(creature);
        
    }
}