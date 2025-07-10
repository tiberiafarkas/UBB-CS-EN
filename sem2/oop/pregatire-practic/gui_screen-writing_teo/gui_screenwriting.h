#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_screenwriting.h"

class gui_screenwriting : public QMainWindow
{
    Q_OBJECT

public:
    gui_screenwriting(QWidget *parent = nullptr);
    ~gui_screenwriting();

private:
    Ui::gui_screenwritingClass ui;
};
