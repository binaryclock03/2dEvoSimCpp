#include "InterNeuron.h"
#include <cmath>
#include <numeric>

InterNeuron::InterNeuron(int address)
{
    this->address = address;
}

void InterNeuron::activate(int action)
{
    switch(action) {
        case 1:
            this->value = tanh(incoming + incomingLast);
        case 2:
            this->incomingLast = this->incomingNext;
            this->incomingNext = 0;
    }
};