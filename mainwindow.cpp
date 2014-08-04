#include "mainwindow.h"
#include <QGridLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
	motorControlAction = new QAction("&Motor Control",this);
	functionMenu = menuBar()->addMenu("&Functions");
	functionMenu->addAction(motorControlAction);
	connect(motorControlAction, SIGNAL(triggered()), this, SLOT(launchMotorControl()));


	executor = new Executor();
    c_pannel=new ControlPannel(this);
	motorControlPannel = new MotorControlPannel();
	connect(c_pannel, SIGNAL(start(const int, const int, const int, const int, const bool,const int)),
		executor, SLOT(startBtnSlot(const int, const int, const int, const int, const bool,const int)));
	connect(c_pannel, SIGNAL(stop()), executor, SLOT(stopBtnSlot()));
	connect(c_pannel, SIGNAL(motorAdvance(const int)), executor, SLOT(motorAdvance(const int)));
	connect(c_pannel, SIGNAL(motorReverse(const int)), executor, SLOT(motorReverse(const int)));
	connect(motorControlPannel, SIGNAL(motorAdvance(const int)), executor, SLOT(motorAdvance(const int)));
	connect(motorControlPannel, SIGNAL(motorReverse(const int)), executor, SLOT(motorReverse(const int)));
	connect(executor, SIGNAL(showData(const double*, const double*, const int)), c_pannel, SLOT(showData(const double*, const double*, const int)));
	connect(executor, SIGNAL(showCurrentWL(const double)), c_pannel, SLOT(showCurrentWL(const double)));
    setCentralWidget(c_pannel);
}

void MainWindow::launchMotorControl(){
	/*int count=2000;
	double *wavelength=new double [count];
	double *amplitude= new double [count];
	for (int i=0;i<count;++i){
	wavelength[i]=2+0.0005*i;
	amplitude[i]=double(i);
	}
	c_pannel->showData(wavelength,amplitude,count);*/
	motorControlPannel->show();
}


