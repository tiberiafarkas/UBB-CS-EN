#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_task.h"

class gui_task : public QMainWindow
{
    Q_OBJECT

public:
    gui_task(QWidget *parent = nullptr);
    ~gui_task();

private:
    Ui::gui_taskClass ui;
};
