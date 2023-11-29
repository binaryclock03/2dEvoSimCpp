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
    float grade = 0.0f;

    ProgressTracker Pt = ProgressTracker(mutationRate, populationSize, true);
    
    Population* pop = new Population();
    pop->generateGenomes(populationSize, 16, funcs.sensorFuncs.size(), funcs.actionFuncs.size(), 4);
    pop->saveGenerationHex();
    pop->saveGeneration();

    
    while(!Pt.targetReached) 
    {   
        

        std::cout << "Generation " << to_string(pop->getGeneration()) << " started." << std::endl;
        ProgressTrackerTimer t("Generation " + to_string(pop->getGeneration()),Pt);

        Simulation sim = Simulation(pop->name);
        sim.buildFromPop(pop);
        sim.optimize();
        sim.simulate(256,pop->getGeneration());


        int numberOfSurvivors;
        numberOfSurvivors = sim.returnSurvivors().size();
        std::cout << "   " << numberOfSurvivors << " Survivors" << std::endl;
        
        Pt.logSurvivorCount(numberOfSurvivors,pop->getGeneration());

        grade = static_cast<float>(numberOfSurvivors) / static_cast<float>(Pt.targetSurvivors);

        //mutationRate = (1.038 - 3.3793*grade + 3.8078*pow(grade,2) - 1.4546*pow(grade,3))*8/10 ;
        mutationRate = (0.2 * exp(-4.14 * grade)) + 0.001;
        //mutationRate = 0.01;
        
        cout << to_string(mutationRate) << endl;

        pop->nextGeneration(mutationRate,sim.returnSurvivors());

        //std:cout << "Grade: " << to_string(grade) << " Mutation Rate: " << to_string(mutationRate) << std::endl;
        
    }
    std::cin.get();
}