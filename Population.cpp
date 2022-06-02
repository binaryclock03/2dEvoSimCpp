#include "Population.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <filesystem>


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
    this->name = name;
}

void Population::generateGenomes(int numberOfGenomes,int genesPerGenome,int maxInIndex,int maxOutIndex,int maxInterIndex) {
    this-> numberOfGenomes = numberOfGenomes;

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
    string generationStr = "";

    string filePath = "Populations//" + this->name + ".csv";

    std::fstream file(filePath, file.app | file.in);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;
    } else {
        string generationStr = "";
       
        file >> generationStr;
        file.close();
    }


}

void reproduce(float mutationRate) {

}

void nextGeneration(forward_list<Genome> survivors, float mutationRate) {

}