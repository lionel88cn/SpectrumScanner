#pragma once
#include <qthread.h>
#include "DAQManager.h"
#define RESOLUTION 5
class Executor :
	public QThread
{
	Q_OBJECT
public:
	Executor();
	~Executor();
Q_SIGNALS:
	void showData(const double *wavelength, const double *amplitude, int count);
	void showCurrentWL(const double currentWL);
public Q_SLOTS:
void startBtnSlot(const int startWL, const int stopWL, const int initialWL, const int msdelay, const bool isRep, const int gratingNum);
	void stopBtnSlot();
	void resetBtnSlot();
	void motorAdvance(int steps);
	void motorReverse(int steps);
private:
	DAQManager *daq;
	int initialWL;
	int startWL;
	int stopWL;
	int gratingNum=1;
	double currentWL;
	int msdelay;
	bool repFlag = 0;
	bool runFlag = 0;
	double *data;
	void run();
};

