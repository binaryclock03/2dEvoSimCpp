// Neuron.h
#include <forward_list>
#pragma once

using namespace std;

class Neuron
{
protected:
    int address;
    int depth;
    float value;
    forward_list<int> incoming;
    forward_list<int> incomingLast;
    forward_list<int> incomingNext;
public:
    Neuron(int address);

    void activate();

    int getAddress() { return this->address; }
    void setAddress(int address) { this->address = address; }

    int getDepth() { return this->depth; }
    void setDepth(int depth) { this->depth = depth; }
};