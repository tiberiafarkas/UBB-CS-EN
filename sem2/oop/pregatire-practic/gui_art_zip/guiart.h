#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_guiart.h"

class guiart : public QMainWindow
{
    Q_OBJECT

public:
    guiart(QWidget *parent = nullptr);
    ~guiart();

private:
    Ui::guiartClass ui;
};
