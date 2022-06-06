#include "InterNeuron.h"
#include "NeuralNet.h"
#include <cmath>
#include <numeric>

InterNeuron::InterNeuron(int address)
{
    this->address = address;
    this->depth = 0;
}

void InterNeuron::activate(int action, NeuralNet* brain, Simulation *simulation)
{
    switch(action) {
        case 1:
            this->value = tanh(incoming + incomingLast);
        case 2:
            this->incomingLast = this->incomingNext;
            this->incomingNext = 0;
    }
};