#include "ejemplo1.h"

ejemplo1::ejemplo1(): Ui_Counter()
{
	setupUi(this);
	show();
	connect(button, SIGNAL(clicked()), this, SLOT(doButton()));
    connect(pushButton, SIGNAL(clicked()), this, SLOT(increase()));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(decrementar()));
	mytimer.connect(std::bind(&ejemplo1::cuenta, this));
    mytimer.start(500);
    aux=0;
}

ejemplo1::~ejemplo1()
{}

void ejemplo1::doButton()
{
	static bool stopped = false;
	stopped = !stopped;
	if(stopped)
		mytimer.stop();
	else
		mytimer.start(500);
	qDebug() << "click on button";
}
void ejemplo1::increase() {
    aux=0;
}
void ejemplo1::cuenta()
{
    if (aux==0){
        lcdNumber->display(++cont);
    }else{
        lcdNumber->display(--cont);
    }
	trick++;
}
void ejemplo1::decrementar() {
    aux=1;
}


