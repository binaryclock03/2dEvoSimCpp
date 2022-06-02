// ActionNeuron.h
#pragma once
#include "Neuron.h"

class ActionNeuron: public Neuron
{
protected:
    void (*actionFunctionPos)(int);
    void (*actionFunctionNeg)(int);
public:
    ActionNeuron(int address);
    ActionNeuron(int address, void (*funcPos)(int), void (*funcNeg)(int));
    void activate(int action);
};