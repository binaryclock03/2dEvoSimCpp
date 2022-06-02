// ActionNeuron.h
#include "Neuron.h"
#pragma once

class ActionNeuron: public Neuron
{
protected:
    void (*actionFunctionPos)(int);
    void (*actionFunctionNeg)(int);
public:
    ActionNeuron(int address, void (*funcPos)(int), void (*funcNeg)(int));
    void activate(int action);
};