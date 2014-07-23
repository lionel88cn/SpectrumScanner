#include "Executor.h"
#include <qinputdialog.h>

Executor::Executor()
{
	daq = new DAQManager();
}


Executor::~Executor()
{
	delete daq;
}

void Executor::startBtnSlot(const int startWL, const int stopWL, const int initialWL, const int msdelay, const bool isRep){
	if (this->isRunning()) return;
	this->startWL = startWL;
	this->stopWL = stopWL;
	this->msdelay = msdelay;
	repFlag = isRep;
	if (initialWL > this->startWL){
		int steps = (initialWL - this->startWL)*RESOLUTION;
		for (int i = 0; i < steps; ++i) {
			daq->motorReverse();
			msleep(1);
			currentWL = double(initialWL) - double(i+1) / double(RESOLUTION);
			emit showCurrentWL(currentWL);
		}
	}
	if (initialWL < this->startWL){
		int steps = (this->startWL - initialWL)*RESOLUTION;
		for (int i = 0; i < steps; ++i) {
			daq->motorAdvance();
			msleep(1);
			currentWL = double(initialWL) + double(i+1) / double(RESOLUTION);
			emit showCurrentWL(currentWL);
		}
	}
	runFlag = 1;
	this->start();
}

void Executor::stopBtnSlot(){
	runFlag = 0;
	repFlag = 0;
}

void Executor::resetBtnSlot(){
	runFlag = 0;
	repFlag = 0;
	this->msleep(100);
	delete daq;
	daq = new DAQManager();
}

void Executor::run(){
	int steps = (stopWL - startWL)*RESOLUTION;
	data = new double[steps];
	for (int i = 0; i < steps; ++i){
		if (!runFlag) return;
		data[i] = daq->getVoltage();
		daq->motorAdvance();
		msleep(msdelay);
		currentWL = double(startWL) + double(i + 1) / double(RESOLUTION);
		emit showCurrentWL(currentWL);
	}
}