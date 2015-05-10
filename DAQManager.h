#pragma once
#include <stdio.h>
#include <qdebug.h>

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
	void trigger();
	void motorAdvance();
	void motorReverse();
	double getVoltage();
	int getNumOfStates();
private:
	bool dataAcquired;
	int stateNum;
	int stateCount;
	uInt32 *states;
	TaskHandle motorTaskHandle;
	TaskHandle adcTaskHandle;
	TaskHandle triggerTaskHandle;
	float64 *voltageData;
public:
	int32 EveryNCallback(TaskHandle taskHandle);
};
int32 CVICALLBACK EveryNCallbackWrapper(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);

