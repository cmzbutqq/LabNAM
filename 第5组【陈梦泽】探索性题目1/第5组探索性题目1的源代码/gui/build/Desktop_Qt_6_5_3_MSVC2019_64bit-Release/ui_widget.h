/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *fin_label;
    QLabel *input_label;
    QPushButton *diagButton;
    QLabel *eps_label;
    QPushButton *horiButton;
    QLabel *frame_label;
    QPushButton *pthButton;
    QLineEdit *pthEdit;
    QLineEdit *frameEdit;
    QLineEdit *resEdit;
    QLineEdit *epsEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(689, 306);
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 60, 671, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        fin_label = new QLabel(gridLayoutWidget);
        fin_label->setObjectName("fin_label");

        gridLayout->addWidget(fin_label, 2, 0, 1, 1);

        input_label = new QLabel(gridLayoutWidget);
        input_label->setObjectName("input_label");

        gridLayout->addWidget(input_label, 0, 0, 1, 1);

        diagButton = new QPushButton(gridLayoutWidget);
        diagButton->setObjectName("diagButton");

        gridLayout->addWidget(diagButton, 2, 2, 1, 1);

        eps_label = new QLabel(gridLayoutWidget);
        eps_label->setObjectName("eps_label");

        gridLayout->addWidget(eps_label, 3, 0, 1, 1);

        horiButton = new QPushButton(gridLayoutWidget);
        horiButton->setObjectName("horiButton");

        gridLayout->addWidget(horiButton, 3, 2, 1, 1);

        frame_label = new QLabel(gridLayoutWidget);
        frame_label->setObjectName("frame_label");

        gridLayout->addWidget(frame_label, 1, 0, 1, 1);

        pthButton = new QPushButton(gridLayoutWidget);
        pthButton->setObjectName("pthButton");

        gridLayout->addWidget(pthButton, 0, 2, 1, 1);

        pthEdit = new QLineEdit(gridLayoutWidget);
        pthEdit->setObjectName("pthEdit");

        gridLayout->addWidget(pthEdit, 0, 1, 1, 1);

        frameEdit = new QLineEdit(gridLayoutWidget);
        frameEdit->setObjectName("frameEdit");

        gridLayout->addWidget(frameEdit, 1, 1, 1, 1);

        resEdit = new QLineEdit(gridLayoutWidget);
        resEdit->setObjectName("resEdit");

        gridLayout->addWidget(resEdit, 2, 1, 1, 1);

        epsEdit = new QLineEdit(gridLayoutWidget);
        epsEdit->setObjectName("epsEdit");

        gridLayout->addWidget(epsEdit, 3, 1, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        fin_label->setText(QCoreApplication::translate("Widget", "FINAL NAME", nullptr));
        input_label->setText(QCoreApplication::translate("Widget", "INPUT_PATH", nullptr));
        diagButton->setText(QCoreApplication::translate("Widget", "DIAGONAL", nullptr));
        eps_label->setText(QCoreApplication::translate("Widget", "EPISILON", nullptr));
        horiButton->setText(QCoreApplication::translate("Widget", "HORIZONTAL", nullptr));
        frame_label->setText(QCoreApplication::translate("Widget", "FRAME NAME", nullptr));
        pthButton->setText(QCoreApplication::translate("Widget", "choose", nullptr));
        pthEdit->setText(QCoreApplication::translate("Widget", "D:/AAADREAMTEAMSAMPLES/my_wife.jpg", nullptr));
        frameEdit->setText(QCoreApplication::translate("Widget", "Framewire.jpg", nullptr));
        resEdit->setText(QCoreApplication::translate("Widget", "Result.jpg", nullptr));
        epsEdit->setText(QCoreApplication::translate("Widget", "20", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
