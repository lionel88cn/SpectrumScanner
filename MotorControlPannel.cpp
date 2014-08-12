#include "MotorControlPannel.h"
#include <qgridlayout.h>

MotorControlPannel::MotorControlPannel()
{
	QGridLayout *layout = new QGridLayout();
	l_steps = new QLabel(this);
    l_steps->setText("STEPS:");
	edit_steps = new QLineEdit(this);
	b_advance = new QPushButton(tr("ADVANCE"), this);
	b_reverse = new QPushButton(tr("REVERSE"), this);
	connect(b_advance, SIGNAL(clicked()), this, SLOT(buttonAdvanceSlot()));
	connect(b_reverse, SIGNAL(clicked()), this, SLOT(buttonReverseSlot()));
	layout->addWidget(l_steps, 0, 0);
	layout->addWidget(edit_steps, 0, 1);
	layout->addWidget(b_advance, 1, 0);
	layout->addWidget(b_reverse, 1, 1);
	this->setLayout(layout);
}


MotorControlPannel::~MotorControlPannel()
{
}

void MotorControlPannel::buttonAdvanceSlot(){
	int steps = edit_steps->text().toInt();
	emit motorAdvance(steps);
}

void MotorControlPannel::buttonReverseSlot(){
	int steps = edit_steps->text().toInt();
	emit motorReverse(steps);
}
