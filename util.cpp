#include <random>

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