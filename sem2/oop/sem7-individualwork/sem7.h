#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sem7.h"

class sem7 : public QMainWindow
{
    Q_OBJECT

public:
    sem7(QWidget *parent = nullptr);
    ~sem7();

private:
    Ui::sem7Class ui;
};

