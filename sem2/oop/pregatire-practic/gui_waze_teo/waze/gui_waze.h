#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_waze.h"

class gui_waze : public QMainWindow
{
    Q_OBJECT

public:
    gui_waze(QWidget *parent = nullptr);
    ~gui_waze();

private:
    Ui::gui_wazeClass ui;
};
