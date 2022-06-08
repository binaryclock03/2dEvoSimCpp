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

void Simulation::simulate(int steps)
{
    this->maxTick = steps;
    for (short i = 0; i < steps; i++)
    {
        this->tick = i;
        this->simulate();
    }
}

void Simulation::simulate(int steps, int generation)
{
    this->maxTick = steps;
    for (short i = 0; i < steps; i++)
    {
        if (generation%10 == 0)
        {
            this->saveState(generation);
        }
        this->tick = i;
        this->simulate();
    }
}

void Simulation::saveState(int generation)
{
    string filePath = "Playbacks/" + this->name + "_" + to_string(generation) + ".csv";

    std::fstream file;
    file.open(filePath, file.app | file.out);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;
    }
    else {
        string stepStr = "";
        for (auto pos:IdPos) {
            stepStr = stepStr + to_string(pos.second) + ",";
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

void Simulation::buildFromPop(Population population)
{
    for (int i = 0; i < population.getNumberOfGenomes(); i++)
    {
        int pos = randInt(0, this->gridBounds[0]*this->gridBounds[1]);
        this->PosId.insert({pos, i});
        this->IdPos.insert({i, pos});

        NeuralNet creature = NeuralNet(i);
        creature.buildNet(population.getGenome(i));
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

        if (y > ((int) this->gridBounds[1]/4) && y < ((int)this->gridBounds[1]*3 / 4) && x >((int)this->gridBounds[0] / 4) && x < ((int)this->gridBounds[0] * 3 / 4))
            survivors.push_back(i);
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
    return (int) this->getCreaturePos(id) / this->gridBounds[1];
}

void Simulation::setCreaturePos(int id, int pos)
{
    if (this->PosId.count(pos) == 0)
    {
        int beforePos = this->IdPos[id];
        this->PosId.erase(beforePos);
        this->PosId.insert({ pos, id });
        this->IdPos[id] = pos;
    }
}

void Simulation::moveCreature(int id, int x, int y)
{
    int pos = this->getCreaturePos(id);

    if ((this->getCreatureX(id) != 0 && this->getCreatureX(id) != this->gridBounds[0]) || (this->getCreatureX(id) == this->gridBounds[0] && x < 0) || (this->getCreatureX(id) == 0 && x > 0))
        pos += x;

    if ((this->getCreatureY(id) != 0 && this->getCreatureY(id) != this->gridBounds[1]) || (this->getCreatureY(id) == this->gridBounds[1] && y < 0) || (this->getCreatureY(id) == 0 && y > 0))
        pos += y*this->gridBounds[0];

    this->setCreaturePos(id, pos);
}
