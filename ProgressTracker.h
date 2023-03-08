#pragma once
#include <iostream>
#include <string>
#include <array>
#include <chrono>

using namespace std;


class ProgressTracker {
public:
	bool targetReached = false;
	ProgressTracker(float mutationRate, int populationSize, bool autoStop);
	void logSurvivorCount(int survivors,int generation);
	void logGenerationTime(float duration);
	int targetSurvivors;

private:
	int pastSurvivors[10] = { 0,0,0,0,0,0,0,0,0,0};
	float lastAverageSurvivors = 0;
	int lastGeneration = 0;
	float lastGenerationTime;
	bool autoStop;
};

struct ProgressTrackerTimer {
	std::chrono::time_point<chrono::steady_clock> start, end;
	std::chrono::duration<double> duration;
	string name = "Unnamed Progress Tracker Timer";
	ProgressTracker &Pt;

	ProgressTrackerTimer(string name, ProgressTracker& Pt);
	~ProgressTrackerTimer();
};