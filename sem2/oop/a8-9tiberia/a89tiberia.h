#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a89tiberia.h"

class a89tiberia : public QMainWindow
{
    Q_OBJECT

public:
    a89tiberia(QWidget *parent = nullptr);
    ~a89tiberia();

private:
    Ui::a89tiberiaClass ui;
};
