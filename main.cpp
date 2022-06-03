#include <iostream>
#include "netObjects/NeuralNet.h"
#include "Genome.h"

using namespace std;

int main()
{
    Genome genome = Genome(4,4,4,4);
    NeuralNet brain = NeuralNet();
    brain.buildNet(genome);
    brain.checkPaths();

    std::cout << brain.getGenes().front().toString() << std::endl;
    std::cin.get();
}