#include "Neuron.h"
#include "NeuralNet.h"

Neuron::Neuron()
{
    this->address = 0;
    this->depth = 0;
    this->incoming = 0;
    this->incomingLast = 0;
    this->incomingNext = 0;
    this->value = 0;
};

Neuron::Neuron(int address)
{
    this->address = address;
    this->depth = 0;
    this->incoming = 0;
    this->incomingLast = 0;
    this->incomingNext = 0;
    this->value = 0;
}

Neuron::~Neuron() {}
