// SensorNeuron.h
#pragma once
#include "Neuron.h"

class SensorNeuron: public Neuron
{
protected:
    float (*sensorFunction)(Neuron*, NeuralNet*);
public:
    SensorNeuron(int address);
    SensorNeuron(int address, float (*sensorFunction)(Neuron*, NeuralNet*));
    void activate(int action, NeuralNet* brain);
};