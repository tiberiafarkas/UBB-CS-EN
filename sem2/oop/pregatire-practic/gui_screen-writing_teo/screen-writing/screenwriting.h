#pragma once

#include <QtWidgets/QWidget>
#include "ui_screenwriting.h"

class screenwriting : public QWidget
{
    Q_OBJECT

public:
    screenwriting(QWidget *parent = nullptr);
    ~screenwriting();

private:
    Ui::screenwritingClass ui;
};

