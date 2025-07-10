#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_patient.h"

class gui_patient : public QMainWindow
{
    Q_OBJECT

public:
    gui_patient(QWidget *parent = nullptr);
    ~gui_patient();

private:
    Ui::gui_patientClass ui;
};
