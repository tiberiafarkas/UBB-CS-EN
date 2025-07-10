#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MedicalDisorders.h"

class MedicalDisorders : public QMainWindow
{
    Q_OBJECT

public:
    MedicalDisorders(QWidget *parent = nullptr);
    ~MedicalDisorders();

private slots:
    void on_showDisorders_clicked();
    void on_showSymptomps_clicked();
    void on_filterDisorders();
    void on_showCategory();

private:
    Ui::MedicalDisordersClass ui;
    void populateList();
    bool shown;
};

