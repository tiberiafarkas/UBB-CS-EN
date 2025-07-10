#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_quiz.h"

class gui_quiz : public QMainWindow
{
    Q_OBJECT

public:
    gui_quiz(QWidget *parent = nullptr);
    ~gui_quiz();

private:
    Ui::gui_quizClass ui;
};
