#include <iostream>
#include "Genome.h"


using namespace std;

int main()
{
    Genome test = Genome(4,4,4,4);
    std::cout << test.genes[0].toString() << std::endl;
    // test.mutate(1);
    // std::cout << test.genes[0].toString() << std::endl;
    // std::cin.get();
    
}