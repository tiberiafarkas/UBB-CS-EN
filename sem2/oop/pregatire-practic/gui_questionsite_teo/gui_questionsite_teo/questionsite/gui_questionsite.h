#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_questionsite.h"

class gui_questionsite : public QMainWindow
{
    Q_OBJECT

public:
    gui_questionsite(QWidget *parent = nullptr);
    ~gui_questionsite();

private:
    Ui::gui_questionsiteClass ui;
};
