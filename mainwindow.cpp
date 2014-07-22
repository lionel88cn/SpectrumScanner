#include "mainwindow.h"

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
    d_plot=new Plot(this);
    setCentralWidget(d_plot);
    d_plot->showData(wavelength,amplitude,count);
}
