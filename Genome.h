// Genome.h
#pragma once 
#include <string>

using namespace std;

struct Gene
{
    int inAdr;
    int outAdr;
    int strength;
    Gene();
    Gene(int inAdr, int outAdr, int strength);
    string toString();
};

class Genome
{
private:
    int numberOfGenes;
    int maxInIndex;
    int maxOutIndex;
    int maxInterIndex;
    
public:
    Genome();
    Genome(int numberOfGenes,int maxInIndex, int maxOutIndex, int maxInterIndex);
    Genome(Gene genes[64],int numberOfGenes,int maxInIndex, int maxOutIndex, int maxInterIndex);
    void mutateGene(int indexOfGene);
    void mutate(float mutationRate);
    int getNumberOfGenes() {return this->numberOfGenes;};
    Genome copy();
    string toString();
    Gene genes[64];
};

