#include <SensorNeuron.h>

SensorNeuron::SensorNeuron(int address, float (*func)(int))
{
    this->address = address;
    this->sensorFunction = func;
};

void SensorNeuron::activate(int action)
{
    switch(action) {
        case 0:
            this->value = this->sensorFunction(1);
            break;
    }
};


