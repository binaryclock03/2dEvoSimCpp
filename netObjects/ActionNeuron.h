// ActionNeuron.h
#pragma once
#include "Neuron.h"

class ActionNeuron: public Neuron
{
protected:
    void (*actionFunctionPos)(Neuron*, NeuralNet*);
    void (*actionFunctionNeg)(Neuron*, NeuralNet*);
public:
    ActionNeuron(int address);
    ActionNeuron(int address, void (*funcPos)(Neuron*, NeuralNet*), void (*funcNeg)(Neuron*, NeuralNet*));
    void activate(int action, NeuralNet* brain);
};