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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Counter
{
public:
    QPushButton *button;
    QLCDNumber *lcdNumber;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSlider *verticalSlider;
    QSlider *verticalSlider_2;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *Counter)
    {
        if (Counter->objectName().isEmpty())
            Counter->setObjectName(QString::fromUtf8("Counter"));
        Counter->resize(691, 300);
        button = new QPushButton(Counter);
        button->setObjectName(QString::fromUtf8("button"));
        button->setGeometry(QRect(80, 180, 251, 71));
        lcdNumber = new QLCDNumber(Counter);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(50, 40, 301, 91));
        pushButton = new QPushButton(Counter);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 150, 89, 25));
        pushButton_2 = new QPushButton(Counter);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 150, 89, 25));
        verticalSlider = new QSlider(Counter);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(450, 40, 16, 160));
        verticalSlider->setMinimum(1);
        verticalSlider->setMaximum(5);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider_2 = new QSlider(Counter);
        verticalSlider_2->setObjectName(QString::fromUtf8("verticalSlider_2"));
        verticalSlider_2->setGeometry(QRect(570, 40, 16, 160));
        verticalSlider_2->setMinimum(1);
        verticalSlider_2->setMaximum(1000);
        verticalSlider_2->setSliderPosition(1000);
        verticalSlider_2->setOrientation(Qt::Vertical);
        textEdit = new QTextEdit(Counter);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(410, 200, 101, 41));
        textEdit_2 = new QTextEdit(Counter);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(540, 200, 81, 41));
        label = new QLabel(Counter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(450, 220, 16, 17));
        label_2 = new QLabel(Counter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(550, 220, 51, 17));
        label_3 = new QLabel(Counter);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(590, 220, 21, 17));

        retranslateUi(Counter);
        QObject::connect(verticalSlider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
        QObject::connect(verticalSlider_2, SIGNAL(valueChanged(int)), label_2, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(Counter);
    } // setupUi

    void retranslateUi(QWidget *Counter)
    {
        Counter->setWindowTitle(QApplication::translate("Counter", "Counter", nullptr));
        button->setText(QApplication::translate("Counter", "STOP", nullptr));
        pushButton->setText(QApplication::translate("Counter", "INCREASE", nullptr));
        pushButton_2->setText(QApplication::translate("Counter", "DECREASE", nullptr));
        textEdit->setHtml(QApplication::translate("Counter", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Incremento:</p></body></html>", nullptr));
        textEdit_2->setHtml(QApplication::translate("Counter", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Periodo:</p></body></html>", nullptr));
        label->setText(QApplication::translate("Counter", "1", nullptr));
        label_2->setText(QApplication::translate("Counter", "1000", nullptr));
        label_3->setText(QApplication::translate("Counter", "ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Counter: public Ui_Counter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTERDLG_H
