#include "mainwindow.h"
#include <QGridLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
	qInstallMessageHandler(MessageWindow::AppendMsgWrapper);
	debugWindow = new MessageWindow();
	executor = new Executor(this);
	motorControlAction = new QAction("&Motor Control",this);
	saveDataAction = new QAction("&Save", this);
	debugWindowAction = new QAction("&Debug Message Window", this);
	functionMenu = menuBar()->addMenu("&Functions");
	functionMenu->addAction(saveDataAction);
	functionMenu->addAction(motorControlAction);
	functionMenu->addAction(debugWindowAction);
	connect(saveDataAction, SIGNAL(triggered()), executor, SLOT(saveActionSlot()));
	connect(motorControlAction, SIGNAL(triggered()), this, SLOT(launchMotorControl()));
	connect(debugWindowAction, SIGNAL(triggered()), this, SLOT(launchDebugWindow()));
	
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
	motorControlPannel->show();
}

void MainWindow::launchDebugWindow()
{
	debugWindow->show();
	QDesktopWidget desktop;
	int desktopHeight = desktop.geometry().height();
	debugWindow->resize(desktopHeight / 2, desktopHeight / 2);
}


