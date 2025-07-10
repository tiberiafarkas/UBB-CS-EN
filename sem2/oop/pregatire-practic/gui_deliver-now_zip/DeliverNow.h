#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DeliverNow.h"

class DeliverNow : public QMainWindow
{
    Q_OBJECT

public:
    DeliverNow(QWidget *parent = nullptr);
    ~DeliverNow();

private:
    Ui::DeliverNowClass ui;
};
