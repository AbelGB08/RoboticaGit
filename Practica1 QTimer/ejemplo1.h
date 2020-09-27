#ifndef ejemplo1_H
#define ejemplo1_H

#include <QtGui>
#include <QTimer>
#include "ui_counterDlg.h"

class ejemplo1 : public QWidget, public Ui_Counter
{
    Q_OBJECT
    public:
        ejemplo1();

    public slots:
        void increase();
        void decrease();
        void doButton();
        void doSlider_2();
        void contar();
        void decrementar();

    private:
        QTimer *timer;
};

#endif // ejemplo1_H
