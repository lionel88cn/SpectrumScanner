#include "Executor.h"
#include <qdebug.h>
#include <QElapsedTimer>

Executor::Executor()
{
	daq = new DAQManager();
}


Executor::~Executor()
{
	delete daq;
}

void Executor::startBtnSlot(const int startWL, const int stopWL, const int initialWL, const int msdelay, const bool isRep,const int gratingNum){
	if (this->isRunning()) return;
	this->startWL = startWL;
	this->stopWL = stopWL;
	this->msdelay = msdelay;
	this->gratingNum = gratingNum;
	this->repFlag = isRep;
	this->initialWL = initialWL;
	runFlag = 1;
	this->start();
}

void Executor::stopBtnSlot(){
	qDebug() << "Executor: Stop";
	runFlag = 0;
	repFlag = 0;
}

void Executor::resetBtnSlot(){
	qDebug() << "Executor: Reset";
	runFlag = 0;
	repFlag = 0;
	this->msleep(100);
	/*delete daq;
	daq = new DAQManager();*/
}

void Executor::run(){
	qDebug() << "Executor: Run";
	if (this->initialWL > this->startWL){
		int steps = (initialWL - this->startWL)*RESOLUTION;
		qDebug() << "Executor: Reverse Back";
		for (int i = 0; i < steps; ++i) {
			currentWL = double(initialWL) - double(i) / double(RESOLUTION);
			currentWL *= this->gratingNum;
			emit showCurrentWL(currentWL);
			daq->motorReverse();
		}
	}
	if (this->initialWL < this->startWL){
		int steps = (this->startWL - initialWL)*RESOLUTION;
		qDebug() << "Executor: Advance Forward";
		for (int i = 0; i < steps; ++i) {
			currentWL = double(initialWL) + double(i) / double(RESOLUTION);
			currentWL *= this->gratingNum;
			emit showCurrentWL(currentWL);
			daq->motorAdvance();
		}
	}


	int steps = (stopWL - startWL)*RESOLUTION;
	qDebug() << "Executor: Advance Forward";
	data = new double[steps];
	double *wlData = new double[steps];
	for (int i = 0; i < steps; ++i){
		if (!runFlag) return;
		currentWL = double(startWL) + double(i) / double(RESOLUTION);
		currentWL *= this->gratingNum;
		wlData[i] = currentWL;
		emit showCurrentWL(currentWL);
		data[i] = daq->getVoltage();
		daq->motorAdvance();
		msleep(msdelay);
	}
	emit showData(wlData, data, steps);
	if (!repFlag) return;
	while (1){
		msleep(500);
		qDebug() << "Executor: Reverse Back";
		for (int i = 0; i < steps; ++i){
			if (!runFlag) return;
			currentWL = double(stopWL) - double(i) / double(RESOLUTION);
			currentWL *= this->gratingNum;
			emit showCurrentWL(currentWL);
			daq->motorReverse();
		}

		msleep(500);
		qDebug() << "Executor: Advance Forward";
		for (int i = 0; i < steps; ++i){
			if (!runFlag) return;
			currentWL = double(startWL) + double(i) / double(RESOLUTION);
			currentWL *= this->gratingNum;
			wlData[i] = currentWL;
			emit showCurrentWL(currentWL);
			data[i] = daq->getVoltage();
			daq->motorAdvance();
			msleep(msdelay);
		}
		emit showData(wlData, data, steps);
	}
}

void Executor::motorAdvance(const int steps)
{
	QElapsedTimer timer;
	timer.start();
	qDebug() << "Motor Advance:"<<steps;
	for (int i = 0; i < steps; ++i){
		daq->motorAdvance();
	}
	qDebug() << "Time elapsed:" << timer.elapsed()<<"ms";
	
}

void Executor::motorReverse(const int steps){
	QElapsedTimer timer;
	timer.start();
	qDebug() << "Motor Reverse:" << steps;
	for (int i = 0; i < steps; ++i){
		daq->motorReverse();
	}
	qDebug() << "Time elapsed:" << timer.elapsed()<<"ms";
}