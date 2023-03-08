#include "ActionNeuron.h"
#include "../util.h"
#include <cmath>
#include <numeric>

ActionNeuron::ActionNeuron(int address, void (*func)(Neuron*, NeuralNet*, Simulation*))
{
    this->incoming = 0;
    this->incomingLast = 0;
    this->incomingNext = 0;
    this->actionFunction = func;
    this->address = address;
    this->depth = 0;
};

float ActionNeuron::activate(int action, NeuralNet* brain, Simulation* simulation)
{
    switch(action) {
        case 1:
            this->value = tanh(incoming + incomingLast);
            return 0.;

        case 2:
            this->incomingLast = this->incomingNext;
            this->incomingNext = 0;
            return 0.;

        case 3:
            this->actionFunction(this, brain, simulation);
            return 0.;
    }
};


