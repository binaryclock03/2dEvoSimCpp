#include <array>
#include <unordered_map>
#include <vector>
#include "netObjects/NeuralNet.h"

using namespace std;

class Simulation
{
protected:
    short gridBounds[2] = {128,128};
    short tick = 0;
    unordered_map<vector<int>, int> positions;
    unordered_map<int, int> creatureIdIndexMap;
    vector<NeuralNet> creatures;
public:
    void simulate();
    void optimize();
};