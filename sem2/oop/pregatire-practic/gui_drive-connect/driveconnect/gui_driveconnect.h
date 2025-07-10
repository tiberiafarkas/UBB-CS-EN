#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_driveconnect.h"

class gui_driveconnect : public QMainWindow
{
    Q_OBJECT

public:
    gui_driveconnect(QWidget *parent = nullptr);
    ~gui_driveconnect();

private:
    Ui::gui_driveconnectClass ui;
};
