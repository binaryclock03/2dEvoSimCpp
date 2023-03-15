#include "Random.h"
#include "util.h"

Random::Random()
{
	this->maxQueueLen = 1000;
}

Random::Random(int maxQueueLen)
{
	this->maxQueueLen = maxQueueLen;
}

float Random::getRandomFloat()
{
	float numb = this->randos.front();
	this->randos.pop();
	return numb;
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

void Random::regenerate()
{
	int queue_len = randos.size();
	for (int i = 0; i < this->maxQueueLen - queue_len; i++)
	{
		this->randos.push(random());
	}
}
