#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plot.h"
#include "controlpannel.h"
#include "Executor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
private:
    ControlPannel* c_pannel;
	Executor *executor;
};

#endif // MAINWINDOW_H
