#pragma once
#include <queue>

using namespace std;

class Random
{
private:
	int seed;

public:
	Random();

	float getRandomFloat();
	float getRandomFloat(float min, float max);

	int getRandomInt(int min, int max);

	bool getRandomBool();
};