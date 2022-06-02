// InterNeuron.h
#include "Neuron.h"
#pragma once

class InterNeuron: public Neuron
{
public:
    void activate();
public:
    InterNeuron(int address);
};