#include "ActionNeuron.h"
#include "../util.h"
#include <cmath>
#include <numeric>

ActionNeuron::ActionNeuron(int address)
{
    this->address = address;
    this->depth = 0;
}

ActionNeuron::ActionNeuron(int address, void (*funcPos)(Neuron*, NeuralNet*, Simulation*), void (*funcNeg)(Neuron*, NeuralNet*, Simulation*))
{
    this->actionFunctionNeg = funcNeg;
    this->actionFunctionPos = funcPos;
    this->address = address;
    this->depth = 0;
};

void ActionNeuron::activate(int action, NeuralNet* brain, Simulation* simulation)
{
    switch(action) {
        case 1:
            this->value = tanh(incoming + incomingLast);
        case 2:
            if(random() < abs(value))
                if(this->value > 0)
                    this->actionFunctionPos(this, brain, simulation);
                else
                    this->actionFunctionNeg(this, brain, simulation);
                break;
            this->incomingLast = this->incomingNext;
            this->incomingNext = 0;
    }
};


