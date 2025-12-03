#pragma once
#include "service.h"
#include <QWidget>

class guiDep : public QWidget 
{
    Q_OBJECT

public:
    guiDep(Service& service, QWidget* parent = nullptr);
    ~guiDep();

private:
    Ui::guiClass ui;
    Service& service;
    void populateList();
    void populateDepartmentList();
    void update();
};