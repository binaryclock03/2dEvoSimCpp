// SensorNeuron.h
#include "Neuron.h"
#pragma once

class SensorNeuron: public Neuron
{
protected:
    float (*sensorFunction)(int);
public:
    SensorNeuron(int address, float (*func)(int));
    void activate(int action);
};