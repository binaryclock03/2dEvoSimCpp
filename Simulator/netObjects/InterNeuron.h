// InterNeuron.h
#pragma once
#include "Neuron.h"

class InterNeuron: public Neuron
{
public:
    InterNeuron(int address);
    float activate(int action, NeuralNet* brain, Simulation *simulation);
};