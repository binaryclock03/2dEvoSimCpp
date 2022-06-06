#include "SensorNeuron.h"
#include "NeuralNet.h"

SensorNeuron::SensorNeuron(int address)
{
    this->address = address;
    this->depth = 0;
}

SensorNeuron::SensorNeuron(int address, float (*sensorFunction)(Neuron*, NeuralNet*, Simulation*))
{
    this->address = address;
    this->sensorFunction = sensorFunction;
    this->depth = 0;
};

void SensorNeuron::activate(int action, NeuralNet* brain, Simulation *simulation)
{
    switch(action) {
        case 0:
            this->value = this->sensorFunction(this, brain, simulation);
            break;
    }
};


