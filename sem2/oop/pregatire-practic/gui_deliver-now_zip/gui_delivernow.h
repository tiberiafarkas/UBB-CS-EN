#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_delivernow.h"

class gui_delivernow : public QMainWindow
{
    Q_OBJECT

public:
    gui_delivernow(QWidget *parent = nullptr);
    ~gui_delivernow();

private:
    Ui::gui_delivernowClass ui;
};
