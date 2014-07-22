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
    c_pannel=new ControlPannel(this);
    setCentralWidget(c_pannel);
    c_pannel->showData(wavelength,amplitude,count);
}
