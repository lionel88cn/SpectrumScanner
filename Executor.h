#pragma once
#include <qthread.h>
#include "DAQManager.h"
#define RESOLUTION 1000
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
	void startBtnSlot(const int startWL, const int stopWL, const int initialWL, const int msdelay, const bool isRep);
	void stopBtnSlot();
	void resetBtnSlot();
private:
	DAQManager *daq;
	int startWL;
	int stopWL;
	double currentWL;
	int msdelay;
	bool repFlag = 0;
	bool runFlag = 0;
	double *data;
	void run();
};

