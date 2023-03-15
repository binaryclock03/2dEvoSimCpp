#include "InterNeuron.h"
#include "NeuralNet.h"
#include <cmath>
#include <numeric>

InterNeuron::InterNeuron(int address)
{
    this->address = address;
    this->depth = 0;
}

float InterNeuron::activate(int action, NeuralNet* brain, Simulation *simulation)
{
    switch(action) {
        case 1:
            this->value = tanh(this->incoming + this->incomingLast);
            return this->value;
        case 2:
            this->incomingLast = this->incomingNext;
            this->incomingNext = 0;
            return 0.;
    }
};