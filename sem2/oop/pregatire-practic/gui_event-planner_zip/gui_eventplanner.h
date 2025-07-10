#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_eventplanner.h"

class gui_eventplanner : public QMainWindow
{
    Q_OBJECT

public:
    gui_eventplanner(QWidget *parent = nullptr);
    ~gui_eventplanner();

private:
    Ui::gui_eventplannerClass ui;
};
