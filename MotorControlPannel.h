#pragma once
#include "qwidget.h"
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
class MotorControlPannel :
	public QWidget
{
	Q_OBJECT
public:
	MotorControlPannel();
	~MotorControlPannel();
Q_SIGNALS:
	void motorAdvance(int steps);
	void motorReverse(int steps);
public Q_SLOTS:
	void buttonAdvanceSlot();
	void buttonReverseSlot();
private:
	QLabel *l_steps;
	QLineEdit *edit_steps;
	QPushButton *b_advance;
	QPushButton *b_reverse;
};

