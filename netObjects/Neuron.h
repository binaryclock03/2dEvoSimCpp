// Neuron.h
#pragma once
#include <forward_list>

using namespace std;

class NeuralNet;

class Neuron
{
protected:
    int address;
    int depth;
    float value;
    int incoming;
    int incomingLast;
    int incomingNext;
public:
    Neuron();
    Neuron(int address);

    void activate(int action, NeuralNet* brain);

    int getAddress() { return this->address; }
    void setAddress(int address) { this->address = address; }

    int getDepth() { return this->depth; }
    void setDepth(int depth) { this->depth = depth; }

    float getValue() { return this->value; }
    void setValue(float value) { this->value = value; }
};