// SensorNeuron.h
#pragma once
#include "Neuron.h"

class SensorNeuron: public Neuron
{
protected:
    float (*sensorFunction)(Neuron*, NeuralNet*, Simulation*);
public:
    SensorNeuron();
    SensorNeuron(int address, float (*sensorFunction)(Neuron*, NeuralNet*, Simulation*));
    void activate(int action, NeuralNet *brain, Simulation *simulation) override;
};