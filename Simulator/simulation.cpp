#include "Simulation.h"
#include "Population.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

Simulation::Simulation(string name) 
{   
    this->name = name;
    this->gridBounds[0] = 128;
    this->gridBounds[1] = 128;
    this->tick = 0;
    this->maxTick = 0;
};

void Simulation::simulate()
{
    for (NeuralNet& creature : this->creatures)
    {
        creature.activate(this);
    }
}

void Simulation::simulate(int steps, int generation)
{
    this->maxTick = steps;

    int playback_interval = 50;

    if (generation%playback_interval == 0)
        this->initializePlayback(generation);

    for (short i = 0; i < maxTick; i++)
    {
        if (generation%playback_interval == 0)
        {
            this->saveState(generation);
        }
        if (i == (int)(maxTick/2))
        {
            for (int j = 0; j < this->creatures.size(); j++)
            {
                int x = this->getCreatureX(j);
                int y = this->getCreatureY(j);

                if (x < ((int)this->gridBounds[0] / 2))
                {
                    this->eraseCreature(j);
                }
            }
        }
        this->tick = i;
        this->simulate();
    }
}

void Simulation::saveState(int generation)
{
    string filePath = "../Playbacks/" + this->name + "_" + to_string(generation) + ".csv";

    std::fstream file;
    file.open(filePath, file.app | file.out);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;
    }
    else {
        string stepStr = "";
        for (auto pos:IdPos) {
            stepStr = stepStr + to_string(pos.first) + ":" + to_string(pos.second) + ",";
        }
        file << stepStr << "\n";
        file.close();
    }
}

void Simulation::initializePlayback(int generation)
{
    string filePath = "../Playbacks/" + this->name + "_" + to_string(generation) + ".csv";

    std::fstream file;
    file.open(filePath, file.app | file.out);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;
    }
    else {
        string stepStr = "";
        for (auto pos : IdPos) {
            stepStr = stepStr + to_string(pos.first) + ":" + this->creatures[pos.first].getGenomeString() + ",";
        }
        file << stepStr << "\n";
        file.close();
    }
}

void Simulation::optimize()
{
    for (NeuralNet& creature : this->creatures)
    {
        creature.optimize();
    }
}

void Simulation::buildFromPop(Population* population)
{
    this->creatures.reserve(population->getNumberOfGenomes());
    for (int i = 0; i < population->getNumberOfGenomes(); i++)
    {
        int pos = randInt(0, this->gridBounds[0]*this->gridBounds[1]);
        this->PosId.insert({pos, i});
        this->IdPos.insert({i, pos});

        NeuralNet creature = NeuralNet(i);
        creature.buildNet(population->getGenome(i));
        this->creatures.push_back(creature);
    }
}

vector<int> Simulation::returnSurvivors()
{
    vector<int> survivors;
    for (int i = 0; i < creatures.size(); i++)
    {
        int x = this->getCreatureX(i);
        int y = this->getCreatureY(i);
        
        if (!(IdPos[i] == -1)) {
            if ((y > 7 * ((int)this->gridBounds[0] / 8)) && (x > 7 * ((int)this->gridBounds[1] / 8))||
                (y < ((int)this->gridBounds[0] / 8)) && (x < ((int)this->gridBounds[1] / 8)) ||
                (y > 7 * ((int)this->gridBounds[0] / 8)) && (x < ((int)this->gridBounds[1] / 8)) ||
                (y < ((int)this->gridBounds[0] / 8)) && (x > 7 * ((int)this->gridBounds[1] / 8)))
                survivors.push_back(i);
        }
    }
    return survivors;
}

int Simulation::getCreaturePos(int id)
{
    return this->IdPos[id];
}

int Simulation::getCreatureX(int id)
{
    return (int) this->getCreaturePos(id) % this->gridBounds[0];
}

int Simulation::getCreatureY(int id)
{
    return (int) (this->getCreaturePos(id) / this->gridBounds[0]);
}

void Simulation::setCreaturePos(int id, int pos)
{
    if (!(IdPos[id] == -1)) {
        if (this->PosId.count(pos) == 0)
        {
            int beforePos = this->IdPos[id];
            this->PosId.erase(beforePos);
            this->PosId.insert({ pos, id });
            this->IdPos[id] = pos;
        }
    }
}

void Simulation::eraseCreature(int id)
{
    int beforePos = this->IdPos[id];
    this->PosId.erase(beforePos);
    this->IdPos[id] = -1;
}

void Simulation::moveCreature(int id, int x, int y)
{
    if (!(IdPos[id] == -1)) {
        int pos = this->getCreaturePos(id);
        int posX = this->getCreatureX(id);
        int posY = this->getCreatureY(id);

        if (!(posX + x >= this->gridBounds[0] || posX + x < 0)) {
            pos += x;
        }

        if (!(posY + y >= this->gridBounds[1] || posY + y < 0)) {
            pos += y * this->gridBounds[0];
        }
        this->setCreaturePos(id, pos);
    }
}
