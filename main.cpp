#include "Simulation.h"
#include "Population.h"

using namespace std;

int main()
{
    Population pop = Population();
    pop.generateGenomes(100, 4, 4, 4, 4);

    Simulation sim = Simulation();
    sim.buildFromPop(pop);
}