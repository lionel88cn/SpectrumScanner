#ifndef CONTROLPANNEL_H
#define CONTROLPANNEL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <plot.h>

class ControlPannel : public QWidget
{
    Q_OBJECT
private:
    QPushButton* b_start;
    QPushButton* b_stop;
    QPushButton* b_reset;
    QLabel* l_begin;
    QLabel* l_end;
    QLabel* l_grating;
    QLineEdit* e_begin;
    QLineEdit* e_end;
    QComboBox* c_grating;
    QCheckBox* cb_isRep;
    Plot* d_plot;

public:
    explicit ControlPannel(QWidget *parent = 0);
Q_SIGNALS:
    void start(const double startWL,const double stopWL, const double speed, const bool isRep);
    void stop();
    void reset();
public Q_SLOTS:
    void showData( const double *wavelength, const double *amplitude, int count );
    void buttonStart();
    void buttonStop();
    void buttonReset();
};

#endif // CONTROLPANNEL_H
