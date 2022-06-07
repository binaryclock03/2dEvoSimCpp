#include "functions.h"
#include <iostream>

NeuronFunctions::NeuronFunctions()
{
    this->sensorFuncs.push_back(alwaysOn);
    this->sensorFuncs.push_back(alwaysOff);
    this->sensorFuncs.push_back(centerBiasX);
    this->sensorFuncs.push_back(centerBiasY);
    this->sensorFuncs.push_back(posX);
    this->sensorFuncs.push_back(posY);

    this->actionFuncs.push_back(moveX);
    this->actionFuncs.push_back(moveY);
    this->actionFuncs.push_back(moveRand);
    this->actionFuncs.push_back(kill);
}

//sensors
float alwaysOn(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    //std::cout << "hello this is always on" << std::endl;
    return 1.0f;
}

float alwaysOff(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    return 0.0f;
}

float centerBiasX(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    return 0.0f;
}

float centerBiasY(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    return 0.0f;
}

float posX(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    return 0.0f;
}

float posY(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    return 0.0f;
}

//actions
void moveX(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{

}

void moveY(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{

}

void moveRand(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{

}

void kill(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{

}