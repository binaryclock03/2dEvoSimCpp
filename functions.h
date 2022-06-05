#include "netObjects/Neuron.h"
#include "netObjects/NeuralNet.h"

//Sensors
float alwaysOn(Neuron* neuron, NeuralNet* brain);
float alwaysOff(Neuron* neuron, NeuralNet* brain);

float centerBiasX(Neuron* neuron, NeuralNet* brain);
float centerBiasY(Neuron* neuron, NeuralNet* brain);

float posX(Neuron* neuron, NeuralNet* brain);
float posY(Neuron* neuron, NeuralNet* brain);

//Actoions
void moveX(Neuron* neuron, NeuralNet* brain);
void moveY(Neuron* neuron, NeuralNet* brain);
void moveRand(Neuron* neuron, NeuralNet* brain);

void kill(Neuron* neuron, NeuralNet* brain);
