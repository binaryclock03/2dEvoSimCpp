#pragma once
#include "Genome.h"
#include <string>
#include <forward_list>
#include <vector>
using namespace std;

class Population {
    public:
    Population();
    Population(string name);
    void generateGenomes(int numberOfGenomes,int genesPerGenome,int maxInIndex,int maxOutIndex,int maxInterIndex);
    void nextGeneration(forward_list<Genome> survivors, float mutationRate);
    void saveGeneration();
    void loadGeneration(int generation);
    int getGeneration() {return this->generation;};
    int getNumberOfGenomes() {return this->numberOfGenomes;};
    private:
     

    string name;
    int numberOfGenomes;
    int generation;
    vector<Genome> genomes;
};