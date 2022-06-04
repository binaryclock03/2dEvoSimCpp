#pragma once
#include <string>
#include <chrono>
#include <iostream>

using namespace std;

int randInt( int min, int max);
float randFloat( float min, float max);
float random();

string intToHex(int toHex,int size);
int hexToInt(string str);

struct Timer
{
    std::chrono::time_point<chrono::system_clock> start, end;
    std::chrono::duration<double> duration;
    string name = "Unnamed Timer";

    
    Timer();
    Timer(string name);
    ~Timer();
};
