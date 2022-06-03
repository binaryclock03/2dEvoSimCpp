// Genome.h
#pragma once 
#include <string>

using namespace std;

struct Gene
{
    char inAdr;
    char outAdr;
    short strength;
    Gene();
    Gene(char inAdr, char outAdr, short strength);
    string toString();
};

class Genome
{
private:
    int numberOfGenes;
    int maxInIndex;
    int maxOutIndex;
    int maxInterIndex;
    Gene genes[64];
    
public:
    Genome();
    Genome(int numberOfGenes,int maxInIndex, int maxOutIndex, int maxInterIndex);
    Genome(Gene genes[64],int numberOfGenes,int maxInIndex, int maxOutIndex, int maxInterIndex);
    Gene getGene(int index);
    void mutateGene(int indexOfGene);
    void mutate(float mutationRate);
    int getNumberOfGenes() {return this->numberOfGenes;};
    Genome copy();
    string toString();
    
};

