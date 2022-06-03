#include <random>
#include <iomanip>
#include <sstream>
#include <string>
#include "util.h"

using namespace std;

int randInt( int min, int max)
 {
    std::random_device                  rand_dev;
    std::mt19937                        gen(rand_dev());
    std::uniform_int_distribution<>    distr(min, max-1);
    return distr(gen);
}

float randFloat( float min, float max)
 {
    std::random_device                  rand_dev;
    std::mt19937                        gen(rand_dev());
    std::uniform_real_distribution<>    distr(min, max-1);
    return distr(gen);
}

float random()
 {
    std::random_device                  rand_dev;
    std::mt19937                        gen(rand_dev());
    std::uniform_real_distribution<>    distr(0,1);
    return distr(gen);
}

string intToHex(int toHex,int size) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(size) << std::hex << toHex;
    return stream.str();
}

int hexToInt(string str) {
    int output;
    std::stringstream stream;
    stream << std::hex << str;
    stream >> output;
    return output;
}