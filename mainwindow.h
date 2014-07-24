#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qmenu.h>
#include <qaction.h>
#include "plot.h"
#include "controlpannel.h"
#include "Executor.h"
#include <qmenubar.h>
#include "MotorControlPannel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
private:
    ControlPannel *c_pannel;
	MotorControlPannel *motorControlPannel;
	Executor *executor;
	QMenu *functionMenu;
	QAction *motorControlAction;
public Q_SLOTS:
	void launchMotorControl();
};

#endif // MAINWINDOW_H
