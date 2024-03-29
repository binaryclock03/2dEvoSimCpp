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
    Genome getGenome(int index);
    void saveGeneration();
    void saveGenerationHex();
    void loadGeneration(int generation);
    int getGeneration() {return this->generation;};
    int getNumberOfGenomes() {return this->numberOfGenomes;};
    void reproduce(float mutationRate);
    void reproduceSex(float mutationRate, vector<int> Survivors);
    void nextGeneration(float mutationRate, vector<int> nonSurvivors);
    string name;
    
private: 
    int numberOfGenomes;
    int genesPerGenome;
    int maxInIndex;
    int maxOutIndex;
    int maxInterIndex;
    int generation;
    vector<Genome> genomes;
};