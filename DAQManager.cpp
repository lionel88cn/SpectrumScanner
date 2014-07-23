#include "DAQManager.h"


DAQManager::DAQManager()
{
	states[0] = 0x8;
	states[1] = 0x4;
	states[2] = 0x2;
	states[3] = 0x1;
	stateNum = 0;
	DAQmxCreateTask("", &motorTaskHandle);
	DAQmxCreateTask("", &adcTaskHandle);
	DAQmxCreateDOChan(motorTaskHandle, "Dev1/port0", "", DAQmx_Val_ChanForAllLines);
	DAQmxCreateAIVoltageChan(adcTaskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL);
	DAQmxCfgSampClkTiming(adcTaskHandle, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, SAMPLE_COUNT);
	DAQmxStartTask(motorTaskHandle);
	DAQmxStartTask(adcTaskHandle);
}


DAQManager::~DAQManager()
{
}

void DAQManager::motorAdvance(){
	uInt32 data;
	int32 written;
	data = states[stateNum];
	DAQmxWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
	stateNum++;
	if (stateNum == stateCount) stateNum = 0;
}

void DAQManager::motorReverse(){
	uInt32 data;
	int32 written;
	data = states[stateNum];
	DAQmxWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
	stateNum--;
	if (stateNum == -1) stateNum = stateCount-1;
}

double DAQManager::getVoltage(){
	float64 data[1000],sum;
	int32 read;
	DAQmxReadAnalogF64(adcTaskHandle, SAMPLE_COUNT, 10.0, DAQmx_Val_GroupByChannel, data, SAMPLE_COUNT, &read, NULL);
	sum = 0;
	for (int i = 0; i < SAMPLE_COUNT; ++i){
		sum += data[i];
	}
	return sum / SAMPLE_COUNT;
}

int DAQManager::getNumOfStates(){
	return stateCount;
}