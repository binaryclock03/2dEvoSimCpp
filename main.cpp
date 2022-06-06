#include "Simulation.h"
#include "Population.h"
#include <iostream>

using namespace std;

int main()
{
    Population pop = Population();
    pop.generateGenomes(100, 4, 4, 4, 4);

    Simulation sim = Simulation();
    sim.buildFromPop(pop);
    sim.simulate();
    sim.optimize();

    for (int i : sim.returnSurvivornts())
    {
        cout << i << " ";
    }
    cout << endl;
    cout << sim.returnSurvivornts().size() << endl;
    cin.get();
}