#pragma once
#include <stdio.h>
#include <NIDAQmx.h>
#define SAMPLE_COUNT 1000
#define SAMPLE_FREQ 10000
class DAQManager
{
public:
	DAQManager();
	~DAQManager();
	void motorAdvance();
	void motorReverse();
	double getVoltage();
	int getNumOfStates();
private:
	int stateNum;
	int stateCount = 4;
	uInt32 states[4];
	TaskHandle motorTaskHandle;
	TaskHandle adcTaskHandle;
};

