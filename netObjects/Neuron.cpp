#include "Neuron.h"

Neuron::Neuron() {} ;

Neuron::Neuron(int address)
{
    this->address = address;
    this->depth = 0;
}
