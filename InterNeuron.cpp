#include "InterNeuron.h"
#include <cmath>
#include <numeric>

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