#include "controlpannel.h"
#include <QGridLayout>
#include <qinputdialog.h>

ControlPannel::ControlPannel(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout* layout=new QGridLayout(this);
    b_start=new QPushButton(this);
    b_start->setText(tr("START"));
    b_stop=new QPushButton(this);
    b_stop->setText(tr("STOP"));
    b_reset=new QPushButton(this);
    b_reset->setText(tr("RESET"));
    l_begin=new QLabel(this);
    l_begin->setText(tr("Begin Wavelength:"));
    l_end=new QLabel(this);
    l_end->setText(tr("End Wavelength:"));
    l_grating=new QLabel(this);
    l_grating->setText(tr("Grating Number:"));
    e_begin=new QLineEdit(this);
    e_end=new QLineEdit(this);
    c_grating=new QComboBox(this);
    cb_isRep=new QCheckBox(this);
    cb_isRep->setText(tr("Repeat"));

    d_plot=new Plot(this);

    layout->addWidget(l_grating,0,0);
    layout->addWidget(c_grating,0,1);
    layout->addWidget(l_begin,1,0);
    layout->addWidget(e_begin,1,1);
    layout->addWidget(l_end,2,0);
    layout->addWidget(e_end,2,1);
    layout->addWidget(cb_isRep,3,0,1,2);

    layout->addWidget(b_start,4,0,1,2);
    layout->addWidget(b_stop,5,0,1,2);
    layout->addWidget(b_reset,6,0,1,2);

    layout->addWidget(d_plot,0,2,7,1);

    setLayout(layout);
    connect(b_start,SIGNAL(clicked()),this,SLOT(buttonStart()));
    connect(b_stop,SIGNAL(clicked()),this,SLOT(buttonStop()));
    connect(b_reset,SIGNAL(clicked()),this,SLOT(buttonReset()));
}

void ControlPannel::showData( const double *wavelength, const double *amplitude, int count )
{
    d_plot->showData(wavelength,amplitude,count);
}

void ControlPannel::buttonStart()
{
    int begin, end, msdelay;
    bool isRep;
	begin = e_begin->text().toInt();
	end = e_end->text().toInt();
	msdelay = 1000;
    isRep=0;
	int currentWL = QInputDialog::getInt(this, tr("Current Position"), tr("Current Position"));
    emit start(begin,end,currentWL,msdelay,isRep);
}

void ControlPannel::buttonStop()
{
    emit stop();
}

void ControlPannel::buttonReset()
{
    emit reset();
}
