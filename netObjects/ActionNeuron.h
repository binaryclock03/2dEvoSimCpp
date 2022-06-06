// ActionNeuron.h
#pragma once
#include "Neuron.h"

class NeuralNet;

class ActionNeuron: public Neuron
{
protected:
    void (*actionFunctionPos)(Neuron*, NeuralNet*, Simulation*);
    void (*actionFunctionNeg)(Neuron*, NeuralNet*, Simulation*);
public:
    ActionNeuron(int address);
    ActionNeuron(int address, void (*funcPos)(Neuron*, NeuralNet*, Simulation*), void (*funcNeg)(Neuron*, NeuralNet*, Simulation*));
    void activate(int action, NeuralNet* brain, Simulation* simulation);
};