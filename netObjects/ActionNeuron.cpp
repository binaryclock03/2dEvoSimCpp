#include "ActionNeuron.h"
#include "../util.h"
#include <cmath>
#include <numeric>

ActionNeuron::ActionNeuron(int address)
{
    this->address = address;
}

ActionNeuron::ActionNeuron(int address, void (*funcPos)(int), void (*funcNeg)(int))
{
    this->address = address;
};

void ActionNeuron::activate(int action)
{
    switch(action) {
        case 1:
            this->value = tanh(incoming + incomingLast);
        case 2:
            if(random() < abs(value))
                if(this->value > 0)
                    this->actionFunctionPos(1);
                else
                    this->actionFunctionNeg(1);
                break;
            this->incomingLast = this->incomingNext;
            this->incomingNext = 0;
    }
};


