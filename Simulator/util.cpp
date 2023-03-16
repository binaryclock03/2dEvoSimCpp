#include <random>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>
#include <iostream>
#include "util.h"
#include "XoshiroCpp.hpp"

using namespace std;

#define RNG_SEED std::chrono::steady_clock::now().time_since_epoch().count()

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


Timer::Timer()
{
    this->name = "Unnamed timer";
    this->start = std::chrono::steady_clock::now();
}

Timer::Timer(string name)
{
    this->name = name;
    this->start = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
    this->end = std::chrono::steady_clock::now();
    this->duration = this->end - this->start;
    std::cout << name <<" took: " << duration.count() << "s" << std::endl;
    std::cout << std::endl;
}

float clamp(float num, float minValue, float maxValue) {
    return std::max(std::min(num, maxValue), minValue);
}

float scale(float x, float inMin, float inMax, float outMin, float outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

int dirX(int dir) {
    if (dir == 2 || dir == 3 || dir == 4) { return 1; }
    else if (dir == 6 || dir == 7 || dir == 8) { return -1; }
    else { return 0; }
}

int dirY(int dir) {
    if (dir == 1 || dir == 2 || dir == 8) { return 1; }
    else if (dir == 4 || dir == 5 || dir == 6) { return -1; }
    else { return 0; }
}