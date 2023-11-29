#include <string>
#include "Genome.h"
#include "util.h"

using namespace std;

Gene::Gene(unsigned char inAdr,unsigned char outAdr, unsigned short strength) {
    this->inAdr = inAdr;
    this->outAdr = outAdr;
    this->strength = strength;
}

Gene::Gene() {
    this->inAdr = 0;
    this->outAdr = 0;
    this->strength = 0;
}

string Gene::toString() 
{
    string inAdr = intToHex(this->inAdr,2);
    string outAdr = intToHex(this->outAdr,2);
    string strength = intToHex(this->strength,4);
    
    string gene = inAdr + outAdr + strength;

    return gene;
}

Genome::Genome() {
    this->numberOfGenes = 0;
    this->maxInIndex = 0;
    this->maxOutIndex = 0;
    this->maxInterIndex = 0;
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
        if (i > maxOutIndex && i > maxInIndex) {
            break;
        }
    } 

    for(int i = 0; i < numberOfGenes; i++) 
    {
        unsigned char inAdr = possibleInAdrs[randInt(0,maxInIndex+maxInterIndex+1)];
        unsigned char outAdr = possibleOutAdrs[randInt(0,maxOutIndex+maxInterIndex+1)];
        unsigned short strength = randInt(0,65536);        
        Gene gene = Gene(inAdr,outAdr,strength);
        this->genes[i] = gene;
    }

}

Genome::Genome(Gene genes[64],int numberOfGenes,int maxInIndex, int maxOutIndex, int maxInterIndex) {
    this->numberOfGenes = numberOfGenes;
    this->maxInIndex = maxInIndex;
    this->maxOutIndex = maxOutIndex;
    this->maxInterIndex = maxInterIndex;

    for (int i = 0; i < numberOfGenes; i++) {
        this->genes[i] = genes[i];
    }
}

Gene Genome::getGene(int index) {
    return this->genes[index];
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
        if (i > this->maxOutIndex && i > this->maxInIndex) {
            break;
        }
    }

    int toChange = randInt(0,3);

    if (toChange == 0) {
        unsigned char newInAdr = possibleInAdrs[randInt(0,this->maxInIndex+this->maxInterIndex+1)];
        this->genes[indexOfGene].inAdr = newInAdr;
    } else if (toChange == 1)
    {
        unsigned char newOutAdr = possibleOutAdrs[randInt(0,this->maxOutIndex+this->maxInterIndex+1)];
        this->genes[indexOfGene].outAdr = newOutAdr;
    } else {
        unsigned short newStrength = randInt(0,65536);
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

string Genome::toString() {
    string genomeStr = "";
    for (int i = 0; i < this->numberOfGenes; i++) {
        genomeStr = genomeStr + this->genes[i].toString();
        if (i < this->numberOfGenes - 1 ) {
            //genomeStr = genomeStr + " ";
        }
    }
    return genomeStr;
}

Genome Genome::copy() {
    return Genome(this->genes,this->numberOfGenes,this->maxInIndex,this->maxOutIndex,this->maxInterIndex);
}
