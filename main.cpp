#include "Simulation.h"
#include "Population.h"
#include <iostream>
#include "util.h"
#include "ProgressTracker.h"

using namespace std;

int main()
{
    float mutationRate = 0.01f;
    int populationSize = 1000;

    ProgressTracker Pt = ProgressTracker(mutationRate, populationSize);
    
    Population *pop = new Population();
    pop->generateGenomes(populationSize, 4, 4, 4, 1);
    pop->saveGeneration();

    
    while(!Pt.targetReached) 
    {   
        std::cout << "Generation " << to_string(pop->getGeneration()) << " started." << std::endl;
        ProgressTrackerTimer t("Generation " + to_string(pop->getGeneration()),Pt);

        Simulation sim = Simulation();
        sim.buildFromPop(*pop);
        sim.optimize();
        sim.simulate(256);


        int numberOfSurvivors;
        numberOfSurvivors = sim.returnSurvivors().size();
        std::cout << "   " << numberOfSurvivors << " Survivors" << std::endl;
        
        Pt.logSurvivorCount(numberOfSurvivors,pop->getGeneration());

        pop->nextGeneration(mutationRate,sim.returnSurvivors());
    }
}