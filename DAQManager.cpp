#include "DAQManager.h"


DAQManager::DAQManager()
{
	stateCount = 8;
	states = new uInt32[stateCount];
	states[0] = 0x8;
	states[1] = 0xC;
	states[2] = 0x4;
	states[3] = 0x6;
	states[4] = 0x2;
	states[5] = 0x3;
	states[6] = 0x1;
	states[7] = 0x9;
	stateNum = 0;
	DAQmxCreateTask("", &motorTaskHandle);
	DAQmxCreateTask("", &adcTaskHandle);
	DAQmxCreateDOChan(motorTaskHandle, "Dev1/port0", "", DAQmx_Val_ChanForAllLines);
	DAQmxCreateAIVoltageChan(adcTaskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL);
	DAQmxCfgSampClkTiming(adcTaskHandle, "", SAMPLE_FREQ, DAQmx_Val_Rising, DAQmx_Val_ContSamps, SAMPLE_COUNT);
	DAQmxStartTask(motorTaskHandle);
	DAQmxStartTask(adcTaskHandle);

	uInt32 data;
	int32 written;
	data = states[0];
	DAQmxWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
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
	Sleep(5);
}

void DAQManager::motorReverse(){
	uInt32 data;
	int32 written;
	data = states[stateNum];
	DAQmxWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
	stateNum--;
	if (stateNum == -1) stateNum = stateCount-1;
	Sleep(5);
}

double DAQManager::getVoltage(){
	float64 *data,sum;
	int32 read;
	data = new float64[SAMPLE_COUNT];
	DAQmxReadAnalogF64(adcTaskHandle, SAMPLE_COUNT, 10.0, DAQmx_Val_GroupByScanNumber, data, SAMPLE_COUNT, &read, NULL);
	sum = 0;
	for (int i = 0; i < SAMPLE_COUNT; ++i){
		sum += data[i];
	}
	return sum / SAMPLE_COUNT;
}

int DAQManager::getNumOfStates(){
	return stateCount;
}
