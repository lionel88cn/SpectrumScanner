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
#include "MessageWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
private:
	MessageWindow *debugWindow;
    ControlPannel *c_pannel;
	MotorControlPannel *motorControlPannel;
	Executor *executor;
	QMenu *functionMenu;
	QAction *debugWindowAction;
	QAction *motorControlAction;
	QAction *saveDataAction;
public Q_SLOTS:
	void launchMotorControl();
	void launchDebugWindow();
};

#endif // MAINWINDOW_H
