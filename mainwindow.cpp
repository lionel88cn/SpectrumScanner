#include "mainwindow.h"
#include <QGridLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    int count=2000;
    double *wavelength=new double [count];
    double *amplitude= new double [count];
    for (int i=0;i<count;++i){
        wavelength[i]=2+0.0005*i;
        amplitude[i]=double(i);
    }
	executor = new Executor();
    c_pannel=new ControlPannel(this);
	connect(c_pannel, SIGNAL(start(const int startWL, const int stopWL, const int initialWL, const int msdelay, const bool isRep)),
		executor, SLOT(startBtnSlot(const int startWL, const int stopWL, const int initialWL, const int msdelay, const bool isRep)));
	connect(c_pannel, SIGNAL(stop()), executor, SLOT(stopBtnSlot()));
	connect(c_pannel, SIGNAL(reset()), executor, SLOT(resetBtnSlot()));
    setCentralWidget(c_pannel);
    c_pannel->showData(wavelength,amplitude,count);
}
