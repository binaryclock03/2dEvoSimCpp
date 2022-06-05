#include "Neuron.h"
#include "NeuralNet.h"

Neuron::Neuron() {} ;

Neuron::Neuron(int address)
{
    this->address = address;
    this->depth = 0;
}

void Neuron::activate(int action, NeuralNet *brain)
{

}
