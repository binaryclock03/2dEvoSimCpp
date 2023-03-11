#include "ProgressTracker.h"
#include <cmath>


ProgressTracker::ProgressTracker(float mutationRate, int populationSize, bool autoStop) {
	this->targetSurvivors = std::floor(populationSize * (1.0f - mutationRate));
	this->autoStop = autoStop;
}

void ProgressTracker::logSurvivorCount(int survivors, int generation) {
	this->pastSurvivors[generation % 10] = survivors;
	float averageSurvivors = 0.0;
	
	if (generation % 10 == 0) {
		
		for (int i = 0; i < 10; i++) {
			averageSurvivors += this->pastSurvivors[i];
		}
		averageSurvivors = averageSurvivors / 10.0;
		float delta = averageSurvivors - this->lastAverageSurvivors;
		float deltaPercent = ((this->lastAverageSurvivors - averageSurvivors) / this->lastAverageSurvivors) * -100.0;
		float targetPercent = (averageSurvivors * 100) / this->targetSurvivors;
		int estimatedGenerations = 1 / (delta / targetSurvivors);

		this->lastAverageSurvivors = averageSurvivors;
		this->lastGeneration = generation;

		std::cout << "Progress Tracker Update:" << std::endl;
		std::cout << "   The average of the last 10 generations increased by " << delta << " or " << deltaPercent << "%." << std::endl;
		std::cout << "   The simulation is at about " << targetPercent << "% of its target." << std::endl;
		std::cout << "   The simulation will reach its target in approximatly " << estimatedGenerations << " generations or about " << this->lastGenerationTime*estimatedGenerations << "s." << std::endl;
	}

	if (averageSurvivors > this->targetSurvivors && this->autoStop) {
		this->targetReached = true;
		std::cout << "Simulation Target Reached" << std::endl;
	}
}

void ProgressTracker::logGenerationTime(float duration) {
	this->lastGenerationTime = duration;
}

ProgressTrackerTimer::ProgressTrackerTimer(string name, ProgressTracker& Pt)
	:Pt(Pt)
{
	this->name = name;
	this->start = std::chrono::high_resolution_clock::now();
	this->Pt = Pt;
}
ProgressTrackerTimer::~ProgressTrackerTimer() {
	this->end = std::chrono::high_resolution_clock::now();
	this->duration = this->end - this->start;
	this->Pt.logGenerationTime(this->duration.count());
	std::cout << name << " took: " << duration.count() << "s" << std::endl;
	std::cout << std::endl;
}