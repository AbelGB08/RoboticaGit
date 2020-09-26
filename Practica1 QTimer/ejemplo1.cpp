#include "ejemplo1.h"

ejemplo1::ejemplo1(): Ui_Counter()
{
	setupUi(this);
	show();
	connect(button, SIGNAL(clicked()), this, SLOT(doButton()) );

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(contar()));
    timer->start(1000);

}

void ejemplo1::doButton()
{
    if (this->button->text() == "STOP")
    {
        this->button->setText(QApplication::translate("Counter", "START", nullptr));
        timer->stop();
    }
    else
    {
        this->button->setText(QApplication::translate("Counter", "STOP", nullptr));
        timer->start();
    }

}

void ejemplo1::doSlider_2()
{
    timer->start(this->verticalSlider_2->value());
}

void ejemplo1::contar()
{
    this->lcdNumber->display(this->lcdNumber->value() + this->verticalSlider->value());
    connect(verticalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(doSlider_2()));
}




