#include "Neuron.h"
#include "NeuralNet.h"
#include <list>

typedef float (*senFunc)(Neuron*, NeuralNet*, Simulation*);
typedef void (*actFunc)(Neuron*, NeuralNet*, Simulation*);

struct NeuronFunctions
{
    NeuronFunctions();
    std::list<senFunc> sensorFuncs;
    std::list<actFunc> actionFuncs;
};

//Sensors
float alwaysOn(Neuron* neuron, NeuralNet* brain, Simulation* simulation);
float alwaysOff(Neuron* neuron, NeuralNet* brain, Simulation* simulation);

float centerBiasX(Neuron* neuron, NeuralNet* brain, Simulation* simulation);
float centerBiasY(Neuron* neuron, NeuralNet* brain, Simulation* simulation);

float posX(Neuron* neuron, NeuralNet* brain, Simulation* simulation);
float posY(Neuron* neuron, NeuralNet* brain, Simulation* simulation);

//Actions
void moveX(Neuron* neuron, NeuralNet* brain, Simulation* simulation);
void moveY(Neuron* neuron, NeuralNet* brain, Simulation* simulation);
void moveRand(Neuron* neuron, NeuralNet* brain, Simulation* simulation);

void kill(Neuron* neuron, NeuralNet* brain, Simulation* simulation);