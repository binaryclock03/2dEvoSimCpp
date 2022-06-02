// SensorNeuron.h
#include "Neuron.h"
#pragma once

class SensorNeuron: public Neuron
{
public:
    void activate(int action);
public:
    SensorNeuron(int address);
};