#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_microbial.h"

class gui_microbial : public QMainWindow
{
    Q_OBJECT

public:
    gui_microbial(QWidget *parent = nullptr);
    ~gui_microbial();

private:
    Ui::gui_microbialClass ui;
};
