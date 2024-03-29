#include "functions.h"

NeuronFunctions::NeuronFunctions()
{
    this->sensorFuncs.push_back(alwaysOn);
    this->sensorFuncs.push_back(alwaysOff);
    this->sensorFuncs.push_back(centerBiasX);
    this->sensorFuncs.push_back(centerBiasY);
    this->sensorFuncs.push_back(posX);
    this->sensorFuncs.push_back(posY);
    this->sensorFuncs.push_back(age);

    this->actionFuncs.push_back(doNothing);
    this->actionFuncs.push_back(moveX);
    this->actionFuncs.push_back(moveY);
    this->actionFuncs.push_back(moveRand);
    this->actionFuncs.push_back(moveFB);
    this->actionFuncs.push_back(moveRL);
    //this->actionFuncs.push_back(kill);
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
    return scale(simulation->getCreatureX(brain->getId()), 0, 128, -1.0, 1.0);
}

float centerBiasY(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    return scale(simulation->getCreatureY(brain->getId()), 0, 128, -1.0, 1.0);
}

float posX(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    return scale(simulation->getCreatureX(brain->getId()), 0, 128, 0, 1.0);
}

float posY(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    return scale(simulation->getCreatureY(brain->getId()), 0, 128, 0, 1.0);
}

float age(Neuron* neuron, NeuralNet* brain, Simulation* simulation) 
{
    return scale(simulation->getSimTick(), 0, simulation->getMaxSimTick(), 0, 1);
}

float getDistCreatureFwd(Neuron* neuron, NeuralNet* brain, Simulation* simulation) 
{
    int dir = brain->getDirection();
    return 0.0f;
}



//actions
void doNothing(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    //HAHA I DO SO MUCH
}

void moveX(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    //cout << "IM MOVING X " << simulation->getCreatureX(brain->getId()) << "," << simulation->getCreatureY(brain->getId()) << endl;
    if (neuron->getValue() > 0)
    {
        simulation->moveCreature(brain->getId(), 1, 0);
        brain->setDirection(3);
    }
    else
    {
        simulation->moveCreature(brain->getId(), -1, 0);
        brain->setDirection(7);
    }
    //cout << "IVE MOVED X " << simulation->getCreatureX(brain->getId()) << "," << simulation->getCreatureY(brain->getId()) << endl;
}

void moveY(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    //cout << "IM MOVING Y " << simulation->getCreatureX(brain->getId()) << "," << simulation->getCreatureY(brain->getId()) << endl;
    if (neuron->getValue() > 0)
    {
        simulation->moveCreature(brain->getId(), 0, 1);
        brain->setDirection(1);
    }
    else
    {
        simulation->moveCreature(brain->getId(), 0, -1);
        brain->setDirection(5);
    }
    //cout << "IVE MOVED Y " << simulation->getCreatureX(brain->getId()) << "," << simulation->getCreatureY(brain->getId()) << endl;
}

void moveRand(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    //cout << "IM MOVING RAND " << simulation->getCreatureX(brain->getId()) << "," << simulation->getCreatureY(brain->getId()) << endl;
    int dir = randInt(1, 9);
    simulation->moveCreature(brain->getId(), dirX(dir), dirY(dir));
    brain->setDirection(dir);
    //cout << "IM MOVING RAND " << simulation->getCreatureX(brain->getId()) << "," << simulation->getCreatureY(brain->getId()) << endl;
}

void moveFB(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    int dir = brain->getDirection();

    if (neuron->getValue() > 0)
    {
        simulation->moveCreature(brain->getId(), dirX(dir), dirY(dir));
    }
    else
    {
        simulation->moveCreature(brain->getId(), -dirX(dir), -dirY(dir));
    }
}

void moveRL(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    int dir = brain->getDirection();
    dir += 2;
    if (dir > 8) { dir -= 8; }

    if (neuron->getValue() > 0)
    {
        simulation->moveCreature(brain->getId(), dirX(dir), dirY(dir));
    }
    else
    {
        simulation->moveCreature(brain->getId(), -dirX(dir), -dirY(dir));
    }
}

void kill(Neuron* neuron, NeuralNet* brain, Simulation* simulation)
{
    //cout << "NOM NOM NOM KINGS BRAINS WERE GO... THERES NOTHING HERE" << endl;
}