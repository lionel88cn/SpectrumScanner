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
#ifdef _WIN32
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
#elif __APPLE__
    DAQmxBaseCreateTask("", &motorTaskHandle);
    DAQmxBaseCreateTask("", &adcTaskHandle);
    DAQmxBaseCreateAIVoltageChan(adcTaskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL);
    DAQmxBaseCfgSampClkTiming(adcTaskHandle,"OnboardClock", SAMPLE_FREQ, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, SAMPLE_COUNT);
    DAQmxBaseCreateDOChan(motorTaskHandle, "Dev1/port0", "", DAQmx_Val_ChanForAllLines);
    DAQmxBaseStartTask(motorTaskHandle);

    uInt32 data;
    int32 written;
    data = states[0];
    DAQmxBaseWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
#endif
}


DAQManager::~DAQManager()
{
#ifdef _WIN32
#elif __APPLE__
    DAQmxBaseStopTask(adcTaskHandle);
    DAQmxBaseStopTask(motorTaskHandle);
#endif
}

void DAQManager::motorAdvance(){
	uInt32 data;
	int32 written;
	data = states[stateNum];
#ifdef _WIN32
	DAQmxWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
	stateNum++;
	if (stateNum == stateCount) stateNum = 0;
	Sleep(5);
#elif __APPLE__
    DAQmxBaseWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
    stateNum++;
    if (stateNum == stateCount) stateNum = 0;
    usleep(5000);
#endif
}

void DAQManager::motorReverse(){

    uInt32 data;
	int32 written;
	data = states[stateNum];
#ifdef _WIN32
	DAQmxWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
	stateNum--;
	if (stateNum == -1) stateNum = stateCount-1;
	Sleep(5);
#elif __APPLE__
    DAQmxBaseWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
    stateNum--;
    if (stateNum == -1) stateNum = stateCount-1;
    usleep(5000);
#endif
}

double DAQManager::getVoltage(){

    float64 data[SAMPLE_COUNT],sum;
    int32 read;
#ifdef _WIN32
	DAQmxReadAnalogF64(adcTaskHandle, SAMPLE_COUNT, 10.0, DAQmx_Val_GroupByScanNumber, data, SAMPLE_COUNT, &read, NULL);
	sum = 0;
	for (int i = 0; i < SAMPLE_COUNT; ++i){
		sum += data[i];
	}
	return sum / SAMPLE_COUNT;
#elif __APPLE__
    DAQmxBaseStartTask(adcTaskHandle);
    DAQmxBaseReadAnalogF64(adcTaskHandle, -1, 10.0, DAQmx_Val_GroupByScanNumber, data, SAMPLE_COUNT, &read, NULL);
    DAQmxBaseStopTask(adcTaskHandle);
    sum = 0;
    for (int i = 0; i < SAMPLE_COUNT; ++i){
        sum += data[i];
    }
    return sum / SAMPLE_COUNT;
#endif
}

int DAQManager::getNumOfStates(){
	return stateCount;
}
