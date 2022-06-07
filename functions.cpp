#include "functions.h"

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
    if (neuron->getValue() > 0) simulation->moveCreature(1, 1, 0);
    else simulation->moveCreature(1, -1, 0);
}

void moveY(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    if (neuron->getValue() > 0) simulation->moveCreature(1, 0, 1);
    else simulation->moveCreature(1, 0, -1);
}

void moveRand(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    int x = randInt(-1, 1);
    int y = randInt(-1, 1);
    simulation->moveCreature(1, x, y);
}

void kill(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    cout << "NOM NOM NOM KINGS BRAINS WERE GO... THERES NOTHING HERE" << endl;
}