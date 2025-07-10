#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_coderevision.h"

class gui_coderevision : public QMainWindow
{
    Q_OBJECT

public:
    gui_coderevision(QWidget *parent = nullptr);
    ~gui_coderevision();

private:
    Ui::gui_coderevisionClass ui;
};
