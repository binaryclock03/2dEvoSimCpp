#include <random>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include "util.h"
#include "XoshiroCpp.hpp"

using namespace std;

#define RNG_SEED std::chrono::system_clock::now().time_since_epoch().count()

int randInt( int min, int max)
 {
    // std::random_device                  rand_dev;
    // std::mt19937                        gen(rand_dev());
    // std::uniform_int_distribution<>    distr(min, max-1);
    
    XoshiroCpp::Xoshiro256StarStar rng(RNG_SEED);

    std::uniform_int_distribution<int> distr(min, max-1);
    return distr(rng);
}

float randFloat( float min, float max)
 {
    XoshiroCpp::Xoshiro256StarStar rng(RNG_SEED);

    std::uniform_real_distribution<float> distr(min, max-1);
    return distr(rng);
}


float random()
 {
    XoshiroCpp::Xoshiro256StarStar rng(RNG_SEED);

    std::uniform_real_distribution<float> distr(0,1);
    return distr(rng);
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