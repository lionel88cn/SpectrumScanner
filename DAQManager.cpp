#include "DAQManager.h"


int32 CVICALLBACK EveryNCallbackWrapper(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData)
{
	DAQManager * this_ = reinterpret_cast<DAQManager*>(callbackData);
	return this_->EveryNCallback(taskHandle);
}
int32 DAQManager::EveryNCallback(TaskHandle taskHandle)
{
	int32       read = 0;
	qDebug() << "Callback Triggered";
	DAQmxReadAnalogF64(taskHandle, SAMPLE_COUNT, 10.0, DAQmx_Val_GroupByScanNumber, voltageData, SAMPLE_COUNT, &read, NULL);
	dataAcquired = 1;
	return 0;
}

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
	dataAcquired = 0;
	voltageData = new float64[SAMPLE_COUNT];
#ifdef _WIN32
	DAQmxCreateTask("", &motorTaskHandle);
	DAQmxCreateTask("", &adcTaskHandle);
	DAQmxCreateTask("", &triggerTaskHandle);

	DAQmxCreateDOChan(motorTaskHandle, "Dev1/port0", "", DAQmx_Val_ChanForAllLines);
	DAQmxCreateDOChan(triggerTaskHandle, "Dev1/port1", "", DAQmx_Val_ChanForAllLines);

	DAQmxCreateAIVoltageChan(adcTaskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL);
	DAQmxCfgSampClkTiming(adcTaskHandle, "", SAMPLE_FREQ, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, SAMPLE_COUNT);
	DAQmxCfgDigEdgeStartTrig(adcTaskHandle, "/Dev1/PFI0", DAQmx_Val_Rising);
	DAQmxRegisterEveryNSamplesEvent(adcTaskHandle, DAQmx_Val_Acquired_Into_Buffer, 1000, 0, EveryNCallbackWrapper, this);

	DAQmxStartTask(motorTaskHandle);
	DAQmxStartTask(triggerTaskHandle);

	uInt32 data;
	int32 written;
	data = states[0];
	DAQmxWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
	data=0x0;
	DAQmxWriteDigitalU32(triggerTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
#elif __APPLE__
    DAQmxBaseCreateTask("motorTask", &motorTaskHandle);
    DAQmxBaseCreateDOChan(motorTaskHandle, "Dev1/port0", "", DAQmx_Val_ChanForAllLines);
    DAQmxBaseStartTask(motorTaskHandle);

    DAQmxBaseCreateTask("adcTask", &adcTaskHandle);
    DAQmxBaseCreateAIVoltageChan(adcTaskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL);
    DAQmxBaseCfgSampClkTiming(adcTaskHandle,"OnboardClock", SAMPLE_FREQ, DAQmx_Val_Rising, DAQmx_Val_ContSamps, SAMPLE_COUNT);
    DAQmxBaseCfgInputBuffer(adcTaskHandle,0);
    DAQmxBaseStartTask(adcTaskHandle);
    uInt32 data;
    int32 written;
    data = states[0];
    DAQmxBaseWriteDigitalU32(motorTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
#endif
}


DAQManager::~DAQManager()
{
#ifdef _WIN32
	DAQmxStopTask(adcTaskHandle);
	DAQmxStopTask(motorTaskHandle);
	DAQmxStopTask(triggerTaskHandle);
#elif __APPLE__
    DAQmxBaseStopTask(adcTaskHandle);
    DAQmxBaseStopTask(motorTaskHandle);
#endif
}

void DAQManager::trigger()
{
	uInt32 data;
	int32 written;
#ifdef _WIN32
	data = 0xFFFF;
	DAQmxWriteDigitalU32(triggerTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
	data = 0x0;
	DAQmxWriteDigitalU32(triggerTaskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL);
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

    float64 sum;
    int32 read;
#ifdef _WIN32
	DAQmxStartTask(adcTaskHandle);
	trigger();
	while(!dataAcquired);
	dataAcquired=0;
	DAQmxStopTask(adcTaskHandle);
#elif __APPLE__
    /*bool32 isDone;
    DAQmxBaseIsTaskDone(adcTaskHandle,&isDone);*/
    DAQmxBaseReadAnalogF64(adcTaskHandle, SAMPLE_COUNT, 10.0, DAQmx_Val_GroupByScanNumber, data, SAMPLE_COUNT, &read, NULL);
    /*while(!isDone);
    DAQmxBaseStopTask(adcTaskHandle);
    DAQmxBaseClearTask(adcTaskHandle);*/
#endif
    sum = 0;
    for (int i = 0; i < SAMPLE_COUNT; ++i){
        sum += voltageData[i];
    }
    return sum / SAMPLE_COUNT;
}

int DAQManager::getNumOfStates(){
	return stateCount;
}
