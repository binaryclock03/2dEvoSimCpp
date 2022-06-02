#include "Population.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>


using namespace std;

Population::Population() {
    char name[5] = {65,65,65,65,0};
    bool invalid = true;
    while (invalid) {
        for (int i = 0; i < 4; i++) {
            name[i] = randInt(65,91);
        }
        string nameStr(name);
        string filePath = "Populations//" + nameStr + ".csv";
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

void Population::saveGeneration() {

    string filePath = "Populations//" + this->name + ".csv";

    std::fstream file(filePath, file.app | file.out);

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

    string filePath = "Populations//" + this->name + ".csv";

    std::fstream file(filePath, file.ate | file.in);
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
                Gene genes[this->genesPerGenome];
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
    if (this->genomes.size() < this->numberOfGenomes) {
        int amountToFill = this->numberOfGenomes - this->genomes.size();
        int currentSize = genomes.size();
        for (int i = 0; i < amountToFill; i++) {
            this->genomes.push_back(this->genomes[randInt(0,amountToFill)].copy());
        }
    }
    for (int i = 0; i < this->numberOfGenomes;i++) {
        this->genomes[i].mutate(mutationRate);
    }
}

void Population::nextGeneration(float mutationRate) {
    this->generation++;
    this->reproduce(mutationRate);
    this->saveGeneration();
}