#include <iostream>
#include "netObjects/NeuralNet.h"
#include "Population.h"
#include <chrono>
#include <ctime> 

using namespace std;

int main()
{
    auto start = std::chrono::system_clock::now();
    //Put code under this

    //Put code above this
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;
    std::cin.get();
}