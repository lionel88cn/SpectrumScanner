#pragma once
#include <stdio.h>
#include <Windows.h>
#include <NIDAQmx.h>
#define SAMPLE_COUNT 20
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
	int32 CVICALLBACK EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
};

