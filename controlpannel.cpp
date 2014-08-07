#include "controlpannel.h"
#include <QGridLayout>
#include <qinputdialog.h>

ControlPannel::ControlPannel(QWidget *parent) :
    QWidget(parent)
{
	QGridLayout *mainLayout = new QGridLayout(this);
    QGridLayout *pannelLayout=new QGridLayout(this);
    b_start=new QPushButton(this);
    b_start->setText(tr("START"));
    b_stop=new QPushButton(this);
    b_stop->setText(tr("STOP"));
    b_advance=new QPushButton(this);
	b_advance->setText(tr("ADVANCE"));
	b_reverse = new QPushButton(this);
	b_reverse->setText(tr("REVERSE"));
    l_begin=new QLabel(this);
    l_begin->setText(tr("Begin Wavelength:"));
    l_end=new QLabel(this);
    l_end->setText(tr("End Wavelength:"));
    l_grating=new QLabel(this);
    l_grating->setText(tr("Grating Number:"));
	l_delay = new QLabel(this);
	l_delay->setText(tr("Step Delay(ms):"));
	l_current = new QLabel(this);
	l_current->setText(tr("Current Wavelength: N/A"));
    e_begin=new QLineEdit(this);
    e_end=new QLineEdit(this);
    c_grating=new QComboBox(this);
	c_grating->addItem(tr("1"));
	c_grating->addItem(tr("2"));
	c_grating->addItem(tr("4"));
	c_grating->setEditable(0);
    cb_isRep=new QCheckBox(this);
    cb_isRep->setText(tr("Repeat"));
	sbox_delay=new QSpinBox(this);
	sbox_delay->setMinimum(0); 
	sbox_delay->setMaximum(1000);
	sbox_delay->setValue(0);
    d_plot=new Plot(this);
    d_plot->setMinimumSize(QSize(500, 500));
    d_plot->setMaximumSize(QSize(500, 500));
	pannelLayout->addWidget(l_grating, 0, 0);
	pannelLayout->addWidget(c_grating, 0, 1);
	pannelLayout->addWidget(l_delay, 1, 0);
	pannelLayout->addWidget(sbox_delay, 1, 1);
	pannelLayout->addWidget(l_begin, 2, 0);
	pannelLayout->addWidget(e_begin, 2, 1);
	pannelLayout->addWidget(l_end, 3, 0);
	pannelLayout->addWidget(e_end, 3, 1);
	pannelLayout->addWidget(cb_isRep, 4, 0);
	pannelLayout->addWidget(l_current, 4, 1);

	pannelLayout->addWidget(b_start, 5, 0, 1, 2);
	pannelLayout->addWidget(b_stop, 6, 0, 1, 2);
	pannelLayout->addWidget(b_advance, 7, 0);
	pannelLayout->addWidget(b_reverse, 7, 1);
	pannelLayout->setColumnStretch(0, 0);
	pannelLayout->setColumnStretch(1, 0);
	mainLayout->addLayout(pannelLayout, 0, 0);
	mainLayout->addWidget(d_plot, 0, 1);
    setLayout(mainLayout);
    connect(b_start,SIGNAL(clicked()),this,SLOT(buttonStart()));
    connect(b_stop,SIGNAL(clicked()),this,SLOT(buttonStop()));
    connect(b_advance,SIGNAL(clicked()),this,SLOT(buttonAdvance()));
	connect(b_reverse, SIGNAL(clicked()), this, SLOT(buttonReverse()));
}

void ControlPannel::showData( const double *wavelength, const double *amplitude, int count )
{
    d_plot->showData(wavelength,amplitude,count);
}

void ControlPannel::buttonStart()
{
    int begin, end, msdelay,gratingNum;
    bool isRep;
	begin = e_begin->text().toInt();
	end = e_end->text().toInt();
	msdelay = sbox_delay->value();
    isRep=cb_isRep->isChecked();
	gratingNum = c_grating->currentText().toInt();
	int currentWL = QInputDialog::getInt(this, tr("Current Position"), tr("Current Position"));
    emit start(begin,end,currentWL,msdelay,isRep,gratingNum);
}

void ControlPannel::buttonStop()
{
    emit stop();
}

void ControlPannel::buttonAdvance()
{
    emit motorAdvance(1);
}

void ControlPannel::buttonReverse()
{
	emit motorReverse(1);
}

void ControlPannel::showCurrentWL(const double currentWL){
	l_current->setText(tr("Current Wavelength:")+QString::number(currentWL)+tr("nm"));
}
