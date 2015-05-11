#pragma once
#include <qthread.h>
#include <qfiledialog.h>
#include <qfile.h>
#include "DAQManager.h"
#define RESOLUTION 16
class Executor : public QThread
{
    enum rotDir {FWD,BWD,INIT};
	Q_OBJECT
public:
	Executor(QWidget *parent);
	~Executor();
Q_SIGNALS:
	void showData(const double *wavelength, const double *amplitude, int count);
	void showCurrentWL(const double currentWL);
public Q_SLOTS:
	void saveActionSlot();
	void startBtnSlot(const int startWL, const int stopWL, const int initialWL, const int msdelay, const bool isRep, const int gratingNum);
	void stopBtnSlot();
	void resetBtnSlot();
	void motorAdvance(const int steps);
	void motorReverse(const int steps);
private:
	QWidget *parent;
	DAQManager *daq;
	int initialWL;
	int startWL;
	int stopWL;
    int gratingNum;
	double currentWL;
	int resolution;
    bool repFlag;
    bool runFlag;
    rotDir rotDirFlag;
	double *data;
	double *wlData;
	int dataCount;
	void run();
    void backlash(rotDir next);
};

