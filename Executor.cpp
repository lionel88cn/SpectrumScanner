#include "Executor.h"
#include <qdebug.h>
#include <QElapsedTimer>

Executor::Executor(QWidget *parent)
{
	this->parent = parent;
    gratingNum=1;
    runFlag=0;
    repFlag=0;
    rotDirFlag=INIT;
	dataCount = 0;
	daq = new DAQManager();
}


Executor::~Executor()
{
	delete daq;
}

void Executor::saveActionSlot()
{
	QString fileName = QFileDialog::getSaveFileName(parent,tr("Save to Text File"), "", tr("Text Files (*.txt)"));
	QFile file(fileName);
	if (file.open(QIODevice::ReadWrite|QIODevice::Truncate))
	{
		QTextStream stream(&file);
		stream << "Wavelength\tAmplitude\r\n";
		for (int i = 0; i < dataCount; ++i){
			stream << wlData[i] << "\t" << data[i]<<"\r\n";
		}
	}
}

void Executor::startBtnSlot(const int startWL, const int stopWL, const int initialWL, const int resolution, const bool isRep,const int gratingNum){
	if (this->isRunning()) return;
	this->startWL = startWL;
	this->stopWL = stopWL;
	this->resolution = resolution;
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
        backlash(BWD);
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
        backlash(FWD);
		for (int i = 0; i < steps; ++i) {
			currentWL = double(initialWL) + double(i) / double(RESOLUTION);
			currentWL *= this->gratingNum;
			emit showCurrentWL(currentWL);
			daq->motorAdvance();
		}
	}


	int steps = (stopWL - startWL)*RESOLUTION/resolution;
	dataCount = steps;
	qDebug() << "Executor: Advance Forward";
    backlash(FWD);
	data = new double[steps];
	wlData = new double[steps];
	for (int i = 0; i < steps; ++i){
		if (!runFlag) return;
		currentWL = double(startWL) + double(i)*resolution / double(RESOLUTION);
		currentWL *= this->gratingNum;
		wlData[i] = currentWL;
		emit showCurrentWL(currentWL);
		data[i] = daq->getVoltage();
		for (int j = 0; j < resolution; ++j) daq->motorAdvance();
	}
	emit showData(wlData, data, steps);
	if (!repFlag) return;
	while (1){
		msleep(500);
		qDebug() << "Executor: Reverse Back";
        backlash(BWD);
		for (int i = 0; i < steps; ++i){
			if (!runFlag) return;
			currentWL = double(stopWL) - double(i)*resolution / double(RESOLUTION);
			currentWL *= this->gratingNum;
			emit showCurrentWL(currentWL);
			for (int j = 0; j < resolution; ++j) daq->motorReverse();
		}

		msleep(500);
		qDebug() << "Executor: Advance Forward";
        backlash(FWD);
		for (int i = 0; i < steps; ++i){
			if (!runFlag) return;
			currentWL = double(startWL) + double(i)*resolution / double(RESOLUTION);
			currentWL *= this->gratingNum;
			wlData[i] = currentWL;
			emit showCurrentWL(currentWL);
			data[i] = daq->getVoltage();
			for (int j = 0; j < resolution; ++j) daq->motorAdvance();
		}
		emit showData(wlData, data, steps);
	}
}

void Executor::motorAdvance(const int steps)
{
	QElapsedTimer timer;
	timer.start();
	qDebug() << "Motor Advance:"<<steps;
    backlash(FWD);
	for (int i = 0; i < steps; ++i){
		daq->motorAdvance();
	}
	qDebug() << "Time elapsed:" << timer.elapsed()<<"ms";
	
}

void Executor::motorReverse(const int steps){
	QElapsedTimer timer;
	timer.start();
	qDebug() << "Motor Reverse:" << steps;
    backlash(BWD);
	for (int i = 0; i < steps; ++i){
		daq->motorReverse();
	}
	qDebug() << "Time elapsed:" << timer.elapsed()<<"ms";
}

void Executor::backlash(rotDir next){
    if (rotDirFlag==FWD&&next==BWD){
        daq->motorReverse();
        daq->motorReverse();
    }
    if (rotDirFlag==BWD&&next==FWD)
    {
        daq->motorAdvance();
        daq->motorAdvance();
    }
    rotDirFlag=next;
}
