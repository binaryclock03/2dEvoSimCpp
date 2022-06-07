#include "SensorNeuron.h"
#include "NeuralNet.h"
#include <iostream>

SensorNeuron::SensorNeuron()
{
    this->address = 0;
    this->sensorFunction = 0;
    this->depth = 0;
    this->incoming = 0;
    this->incomingLast = 0;
    this->incomingNext = 0;
    this->value = 0;
}

SensorNeuron::SensorNeuron(int address, float (*sensorFunction)(Neuron*, NeuralNet*, Simulation*))
{
    this->address = address;
    this->sensorFunction = sensorFunction;
    this->depth = 0;
    this->incoming = 0;
    this->incomingLast = 0;
    this->incomingNext = 0;
    this->value = 0;
};

void SensorNeuron::activate(int action, NeuralNet* brain, Simulation *simulation)
{
    switch(action) {
        case 0:
            this->value = this->sensorFunction(this, brain, simulation);
            break;
    }
};