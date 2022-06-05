#include "Simulation.h"

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