/********************************************************************************
** Form generated from reading UI file 'CourierView.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURIERVIEW_H
#define UI_COURIERVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourierViewClass
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *zoneComboBox;
    QPushButton *deliverButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CourierViewClass)
    {
        if (CourierViewClass->objectName().isEmpty())
            CourierViewClass->setObjectName("CourierViewClass");
        CourierViewClass->resize(600, 400);
        centralWidget = new QWidget(CourierViewClass);
        centralWidget->setObjectName("centralWidget");
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(70, 70, 256, 192));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 50, 221, 16));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(320, 50, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        zoneComboBox = new QComboBox(centralWidget);
        zoneComboBox->setObjectName("zoneComboBox");
        zoneComboBox->setGeometry(QRect(166, 270, 161, 32));
        deliverButton = new QPushButton(centralWidget);
        deliverButton->setObjectName("deliverButton");
        deliverButton->setGeometry(QRect(70, 270, 88, 34));
        CourierViewClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CourierViewClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 30));
        CourierViewClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CourierViewClass);
        mainToolBar->setObjectName("mainToolBar");
        CourierViewClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CourierViewClass);
        statusBar->setObjectName("statusBar");
        CourierViewClass->setStatusBar(statusBar);

        retranslateUi(CourierViewClass);

        QMetaObject::connectSlotsByName(CourierViewClass);
    } // setupUi

    void retranslateUi(QMainWindow *CourierViewClass)
    {
        CourierViewClass->setWindowTitle(QCoreApplication::translate("CourierViewClass", "CourierView", nullptr));
        label->setText(QCoreApplication::translate("CourierViewClass", "TextLabel", nullptr));
        deliverButton->setText(QCoreApplication::translate("CourierViewClass", "Deliver", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourierViewClass: public Ui_CourierViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURIERVIEW_H
