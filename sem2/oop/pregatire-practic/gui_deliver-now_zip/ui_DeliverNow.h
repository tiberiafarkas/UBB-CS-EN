/********************************************************************************
** Form generated from reading UI file 'DeliverNow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELIVERNOW_H
#define UI_DELIVERNOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeliverNowClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DeliverNowClass)
    {
        if (DeliverNowClass->objectName().isEmpty())
            DeliverNowClass->setObjectName("DeliverNowClass");
        DeliverNowClass->resize(600, 400);
        centralWidget = new QWidget(DeliverNowClass);
        centralWidget->setObjectName("centralWidget");
        DeliverNowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DeliverNowClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        DeliverNowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DeliverNowClass);
        mainToolBar->setObjectName("mainToolBar");
        DeliverNowClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DeliverNowClass);
        statusBar->setObjectName("statusBar");
        DeliverNowClass->setStatusBar(statusBar);

        retranslateUi(DeliverNowClass);

        QMetaObject::connectSlotsByName(DeliverNowClass);
    } // setupUi

    void retranslateUi(QMainWindow *DeliverNowClass)
    {
        DeliverNowClass->setWindowTitle(QCoreApplication::translate("DeliverNowClass", "DeliverNow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeliverNowClass: public Ui_DeliverNowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELIVERNOW_H
