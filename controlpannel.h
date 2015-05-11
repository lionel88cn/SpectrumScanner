#ifndef CONTROLPANNEL_H
#define CONTROLPANNEL_H

#define RESOLUTION 16

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <qspinbox.h>
#include <qdesktopwidget.h>
#include "plot.h"

class ControlPannel : public QWidget
{
    Q_OBJECT
private:
    QPushButton* b_start;
    QPushButton* b_stop;
    QPushButton* b_advance;
	QPushButton* b_reverse;
    QLabel* l_begin;
    QLabel* l_end;
    QLabel* l_grating;
	QLabel* l_resolution;
	QLabel* l_current;
    QLineEdit* e_begin;
    QLineEdit* e_end;
    QComboBox* c_grating;
	QComboBox* cbox_resolution;
    QCheckBox* cb_isRep;
    Plot* d_plot;

public:
    explicit ControlPannel(QWidget *parent = 0);
Q_SIGNALS:
	void start(const int startWL, const int stopWL, const int initialWL, const int msdelay, const bool isRep, const int gratingNum);
    void stop();
	void motorAdvance(const int steps);
	void motorReverse(const int steps);
public Q_SLOTS:
    void showData( const double *wavelength, const double *amplitude, int count );
	void showCurrentWL(const double currentWL);
    void buttonStart();
    void buttonStop();
	void buttonAdvance();
	void buttonReverse();
};

#endif // CONTROLPANNEL_H
