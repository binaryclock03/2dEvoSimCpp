#include "SensorNeuron.h"

SensorNeuron::SensorNeuron(int address)
{
    this->address = address;
    this->depth = 0;
}

SensorNeuron::SensorNeuron(int address, float (*func)(int))
{
    this->address = address;
    this->sensorFunction = func;
    this->depth = 0;
};

void SensorNeuron::activate(int action)
{
    switch(action) {
        case 0:
            this->value = this->sensorFunction(1);
            break;
    }
};


