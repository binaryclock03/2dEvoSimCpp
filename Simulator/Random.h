#pragma once
#include <queue>

using namespace std;

class Random
{
private:
	queue<float> randos;
	int maxQueueLen;

public:
	Random(int queue_len);

	float getRandomFloat();
	float getRandomFloat(float min, float max);

	int getRandomInt(int min, int max);

	bool getRandomBool();

	void regenerate();
};