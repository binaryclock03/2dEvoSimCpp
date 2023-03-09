#include "Population.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>


using namespace std;

Population::Population() {
    this->generation = 0;
    char name[5] = {65,65,65,65,0};
    bool invalid = true;
    while (invalid) {
        for (int i = 0; i < 4; i++) {
            name[i] = randInt(65,91);
        }
        string nameStr(name);
        string filePath = "Populations/" + nameStr + ".csv";
        invalid = std::filesystem::exists(filePath);
        this->name = nameStr;
    }

}

Population::Population(string name) {
    this->generation = 0;
    this->name = name;
}

void Population::generateGenomes(int numberOfGenomes,int genesPerGenome,int maxInIndex,int maxOutIndex,int maxInterIndex) {
    this-> numberOfGenomes = numberOfGenomes;
    this-> genesPerGenome = genesPerGenome;
    this->maxInIndex = maxInIndex;
    this->maxOutIndex = maxOutIndex;
    this->maxInterIndex = maxInterIndex;
    

    for (int i = 0; i < numberOfGenomes; i++) {
        this->genomes.push_back(Genome(genesPerGenome,maxInIndex,maxOutIndex,maxInterIndex));
    }

}

Genome Population::getGenome(int index) 
{
    return this->genomes[index];
}

void Population::saveGeneration() {

    string filePath = "Populations/" + this->name + ".csv";

    std::fstream file;
    file.open(filePath, file.app | file.out);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;

    } else {
        string generationStr = "";
        for (int i = 0; i < this->numberOfGenomes; i++) {
            generationStr = generationStr + this->genomes[i].toString(); 
            if (i < this->numberOfGenomes -1) {
                generationStr = generationStr + ",";
            }
        }
        file << generationStr << "\n";
        file.close();
    }
}

void Population::loadGeneration(int generation) {

    string filePath = "Populations/" + this->name + ".csv";

    std::fstream file; 
    file.open(filePath, file.ate | file.in);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;
    } else {
        
        if (file.tellp() == !(36*this->numberOfGenomes*(generation) + (generation))) {
            std::cout << "Generation: " << generation << " does not exist in file: " << filePath << std::endl;
        } else {
            int position = 9*this->genesPerGenome*this->numberOfGenomes*generation + generation;
            file.seekp(position);
        
            vector<Genome> genomes;
            for (int i = 0; i < this->numberOfGenomes; i++) {
                Gene genes[64];
                for (int ii = 0; ii < 64; ii++) {
                    int test = 0;
                    Gene gene = Gene(0,0,0);
                    string geneStr;
                    file >> geneStr;
                    
                    gene.inAdr = hexToInt(geneStr.substr(0,2));
                    gene.outAdr = hexToInt(geneStr.substr(2,2));
                    gene.strength = hexToInt(geneStr.substr(4,4));

                    genes[ii] = gene;
                    if (ii >= genesPerGenome) {
                        break;
                    }
                }
                Genome genome = Genome(genes,this->genesPerGenome,this->maxInIndex,this->maxOutIndex,this->maxInterIndex);
                genomes.push_back(genome);
            }
            this->genomes = genomes;
        }
        file.close();
    }


}

void Population::reproduce(float mutationRate) {
    if (this->genomes.size() < this->numberOfGenomes && this->genomes.size() != 0) {
        int amountToFill = this->numberOfGenomes - this->genomes.size();
        int currentSize = genomes.size();
        for (int i = 0; i < amountToFill; i++) {
            this->genomes.push_back(this->genomes[randInt(0,currentSize)].copy());
        }
    }
    else if (this->genomes.size() == 0)
    {
        this->generateGenomes(this->numberOfGenomes, this->genesPerGenome, this->maxInIndex, this->maxOutIndex, this->maxInterIndex);
    }
    for (int i = 0; i < this->numberOfGenomes;i++) {
        this->genomes[i].mutate(mutationRate);
    }
}

void Population::reproduceSex(float mutationRate, vector<int> survivors) {
    
    //Each survivor reproduces with another survivor, extras are removed, if there are not enough the space is filled w/ reproduce
    //Each mating pair creates 2 offspring
    //Offspring will contain a mix of genes from each parent and a random number of mutated genes (follows mutation rate

    //Cylce through each pair and mix their genes, apply mutations
    //If the end of the vector is reacher deleted the last one if it is the odd on out

    //Fill empty space with new genomes, clone from existing or other?
    //Apply changes to genomes

    

    int numberOfSurvivors = survivors.size();
    int childrenPerPair = 2;

    vector<Genome> children;
    children.reserve(numberOfSurvivors);

    //Create Children --- mutation rate not implemented

    for (int i = 0; i < numberOfSurvivors/2 - numberOfSurvivors%2; i++) {
        
        if (i >= 250) {
            break;
        }

        for (int j = 0; j < childrenPerPair; j++) {
            Gene childGenes[64];
            for (int k = 0; k < this->genesPerGenome; k++) {

                if (randInt(0, 1)) {
                    childGenes[k] = this->genomes[survivors[i]].getGene(k);
                }
                else {
                    childGenes[k] = this->genomes[survivors[i + numberOfSurvivors / 2]].getGene(k);
                }
            }
            Genome child = Genome(childGenes, this->genesPerGenome, this->maxInIndex, this->maxOutIndex, this->maxInterIndex);
            this->genomes.push_back(child);
        }
    }

}

void Population::nextGeneration(float mutationRate, vector<int> survivors) {
    this->generation++;

    survivors.shrink_to_fit();
    
    vector<Genome> newGenomes;
    newGenomes.reserve(this->numberOfGenomes);
    int j = 0;

    for (int i = 0; i < this->numberOfGenomes; i++) {
        if (j >= survivors.size()) {
            break;
        }
        if (i == survivors[j]) {
            newGenomes.push_back(this->genomes[i]);
            j++;
        }
    }

    this->genomes = newGenomes;
    this->reproduceSex(mutationRate, survivors);
    this->reproduce(mutationRate);
    this->saveGeneration();
}