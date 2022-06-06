#include "Simulation.h"
#include "Population.h"
#include <iostream>
#include "util.h"

using namespace std;

int main()
{
    Population pop = Population();
    pop.generateGenomes(1000, 4, 4, 4, 1);
    //pop.saveGeneration();

    Simulation sim = Simulation();
    while(true) { Timer t("Main Loop Timer");
    sim.buildFromPop(pop);
    sim.simulate(256);
    sim.optimize();

    pop.nextGeneration(0.01f,sim.returnSurvivors());



    // for (int i : sim.returnNonSurvivors())
    // {
    //     cout << i << " ";
    // }
    // cout << endl;
    // cout << sim.returnNonSurvivors().size() << endl;
    
    }
    cout << endl;
    cout << sim.returnSurvivors().size() << endl;
    cin.get();
}