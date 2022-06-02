// InterNeuron.h
#include "Neuron.h"
#pragma once

class InterNeuron: public Neuron
{
public:
    InterNeuron(int address);
    void activate(int action);
};