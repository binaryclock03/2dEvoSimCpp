#include <chrono>
#include <random>
#include "Random.h"
#include "util.h"
#include "XoshiroCpp.hpp"

Random::Random()
{
	this->seed = std::chrono::system_clock::now().time_since_epoch().count();
}

float Random::getRandomFloat()
{

	XoshiroCpp::Xoshiro256StarStar rng(this->seed);

	std::uniform_real_distribution<float> distr(0, 1);

	this->seed++;
	return distr(rng);
}

float Random::getRandomFloat(float min, float max)
{
	float numb = this->getRandomFloat();
	float scale = (max - min);
	return (numb * scale) + min;
}

int Random::getRandomInt(int min, int max)
{
	return (int)this->getRandomFloat(min, max);
}

bool Random::getRandomBool()
{
	return (this->getRandomFloat() > 0.5);
}
