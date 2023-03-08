// ActionNeuron.h
#pragma once
#include "Neuron.h"

class NeuralNet;

class ActionNeuron: public Neuron
{
protected:
    void (*actionFunction)(Neuron*, NeuralNet*, Simulation*);
public:
    ActionNeuron(int address, void(*func)(Neuron*, NeuralNet*, Simulation*));
    float activate(int action, NeuralNet* brain, Simulation* simulation);
};