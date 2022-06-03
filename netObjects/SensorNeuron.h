// SensorNeuron.h
#pragma once
#include "Neuron.h"

class SensorNeuron: public Neuron
{
protected:
    float (*sensorFunction)(int);
public:
    SensorNeuron(int address);
    SensorNeuron(int address, float (*func)(int));
    void activate(int action);
};