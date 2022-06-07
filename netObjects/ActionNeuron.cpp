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

void ActionNeuron::activate(int action, NeuralNet* brain, Simulation* simulation)
{
    switch(action) {
        case 1:
            this->value = tanh(incoming + incomingLast);
            break;
        case 2:
            if (true)//random() < abs(value)
            {
                this->actionFunction(this, brain, simulation);
            }
            this->incomingLast = this->incomingNext;
            this->incomingNext = 0;
            break;
    }
};


