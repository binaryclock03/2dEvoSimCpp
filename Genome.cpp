#include <string>
#include "Genome.h"
#include <random>
#include "util.cpp"


using namespace std;



Gene::Gene(int inAdr, int outAdr, int strength) {
    this->inAdr = inAdr;
    this->outAdr = outAdr;
    this->strength = strength;
}

string Gene::toString() 
{
    char inAdrStr[2];
    sprintf(inAdrStr, "%0*x" ,2, this->inAdr);

    char outAdrStr[2];
    sprintf(outAdrStr,"%0*x" ,2, this->outAdr);

    char strengthStr[4];
        sprintf(strengthStr,"%0*x" ,2, this->strength);
    
    char geneAr[8] = {inAdrStr[0],inAdrStr[1],outAdrStr[0],outAdrStr[1],strengthStr[0],strengthStr[1],strengthStr[2],strengthStr[3]};
    
    string gene(geneAr);

    return gene;
}


Genome::Genome(int numberOfGenes,int maxInIndex, int maxOutIndex, int maxInterIndex) 
{
    this->numberOfGenes = numberOfGenes;
    this->maxInIndex = maxInIndex;
    this->maxOutIndex = maxOutIndex;
    this->maxInterIndex = maxInterIndex;

    int possibleInAdrs[128];
    int possibleOutAdrs[128];

    for (int i = 0;i < 128; i++) {
        if (i < maxInIndex) {
            possibleInAdrs[i] = i;
            possibleInAdrs[i+maxInIndex] = i + 128;
        }
        if (i < maxOutIndex) {
            possibleOutAdrs[i] = i;
            possibleOutAdrs[i+maxOutIndex] = i + 128;

        }
        if (i < maxOutIndex && i < maxInIndex) {
            break;
        }
    } 

    for(int i = 0; i < numberOfGenes; i++) 
    {
        int inAdr = possibleInAdrs[randInt(0,maxInIndex)];
        int outAdr = possibleOutAdrs[randInt(0,maxOutIndex)];
        int strength = randInt(0,65536);        
        Gene gene = Gene(inAdr,outAdr,strength);
        this->genes[i] = gene;
    }

}

void Genome::mutateGene(int indexOfGene) {
    if (indexOfGene < 0) {
        indexOfGene = randInt(0,this->numberOfGenes);
    }

    int possibleInAdrs[128];
    int possibleOutAdrs[128];

    for (int i = 0;i < 128; i++) {
        if (i < this->maxInIndex) {
            possibleInAdrs[i] = i;
            possibleInAdrs[i+this->maxInIndex] = i + 128;
        }
        if (i < this->maxOutIndex) {
            possibleOutAdrs[i] = i;
            possibleOutAdrs[i+this->maxOutIndex] = i + 128;
        }
        if (i < this->maxOutIndex && i < this->maxInIndex) {
            break;
        }
    }

    int toChange = randInt(0,2);

    if (toChange == 0) {
        int newInAdr = possibleInAdrs[randInt(0,this->maxInIndex)];
        this->genes[indexOfGene].inAdr = newInAdr;
    } else if (toChange == 1)
    {
        int newOutAdr = possibleOutAdrs[randInt(0,this->maxOutIndex)];
        this->genes[indexOfGene].outAdr = newOutAdr;
    } else {
        int newStrength = randInt(0,65536);
        this->genes[indexOfGene].strength = newStrength;
    }


}

void Genome::mutate(float mutationRate) {
    for (int i = 0; i < this->numberOfGenes; i++) {
        if (random() < mutationRate) {
            this->mutateGene(i);
        }
    }
}

