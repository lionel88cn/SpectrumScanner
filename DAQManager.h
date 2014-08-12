#pragma once
#include <stdio.h>

#ifdef _WIN32
    #include <Windows.h>
    #include <NIDAQmx.h>
#elif __APPLE__
    #include <unistd.h>
    #include <NIDAQmxBase.h>
#endif

#define SAMPLE_COUNT 1000
#define SAMPLE_FREQ 10000.0
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
	int stateCount;
	uInt32 *states;
	TaskHandle motorTaskHandle;
	TaskHandle adcTaskHandle;
};

