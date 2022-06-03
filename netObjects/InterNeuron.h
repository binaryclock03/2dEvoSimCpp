// InterNeuron.h
#pragma once
#include "Neuron.h"

class InterNeuron: public Neuron
{
public:
    InterNeuron(int address);
    void activate(int action);
};