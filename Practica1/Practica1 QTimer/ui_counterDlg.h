/********************************************************************************
** Form generated from reading UI file 'counterDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTERDLG_H
#define UI_COUNTERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Counter
{
public:
    QPushButton *button;
    QLCDNumber *lcdNumber;
    QSlider *verticalSlider;
    QSlider *verticalSlider_2;
    QPlainTextEdit *plainTextEdit;
    QPlainTextEdit *plainTextEdit_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton1;

    void setupUi(QWidget *Counter)
    {
        if (Counter->objectName().isEmpty())
            Counter->setObjectName(QString::fromUtf8("Counter"));
        Counter->resize(620, 270);
        button = new QPushButton(Counter);
        button->setObjectName(QString::fromUtf8("button"));
        button->setGeometry(QRect(80, 180, 251, 71));
        lcdNumber = new QLCDNumber(Counter);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(50, 40, 301, 91));
        verticalSlider = new QSlider(Counter);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(410, 40, 16, 160));
        verticalSlider->setMinimum(1);
        verticalSlider->setMaximum(5);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider_2 = new QSlider(Counter);
        verticalSlider_2->setObjectName(QString::fromUtf8("verticalSlider_2"));
        verticalSlider_2->setGeometry(QRect(530, 40, 16, 160));
        verticalSlider_2->setMinimum(1);
        verticalSlider_2->setMaximum(1000);
        verticalSlider_2->setSliderPosition(1000);
        verticalSlider_2->setOrientation(Qt::Vertical);
        plainTextEdit = new QPlainTextEdit(Counter);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(370, 210, 91, 41));
        plainTextEdit_2 = new QPlainTextEdit(Counter);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(510, 210, 81, 41));
        label = new QLabel(Counter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(410, 230, 31, 20));
        label_2 = new QLabel(Counter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(520, 230, 41, 17));
        label_3 = new QLabel(Counter);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(560, 230, 67, 17));
        pushButton = new QPushButton(Counter);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 150, 89, 25));
        pushButton1 = new QPushButton(Counter);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        pushButton1->setGeometry(QRect(240, 150, 89, 25));

        retranslateUi(Counter);
        QObject::connect(verticalSlider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
        QObject::connect(verticalSlider_2, SIGNAL(valueChanged(int)), label_2, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(Counter);
    } // setupUi

    void retranslateUi(QWidget *Counter)
    {
        Counter->setWindowTitle(QApplication::translate("Counter", "Counter", nullptr));
        button->setText(QApplication::translate("Counter", "STOP", nullptr));
        plainTextEdit->setPlainText(QApplication::translate("Counter", "Incremento", nullptr));
        plainTextEdit_2->setPlainText(QApplication::translate("Counter", "  Periodo", nullptr));
        label->setText(QApplication::translate("Counter", "1", nullptr));
        label_2->setText(QApplication::translate("Counter", "1000 ", nullptr));
        label_3->setText(QApplication::translate("Counter", "ms", nullptr));
        pushButton->setText(QApplication::translate("Counter", "INCREASE", nullptr));
        pushButton1->setText(QApplication::translate("Counter", "DECREASE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Counter: public Ui_Counter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTERDLG_H
