//
// Created by teodo on 6/20/2024.
//

#ifndef EVENT_PLANNER_GUI_H
#define EVENT_PLANNER_GUI_H

#include <QWidget>
#include "Observer.h"
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget, public Observer{
Q_OBJECT

public:
    explicit GUI(Service &serv, Person pers, QWidget *parent = nullptr);

    ~GUI() override;

    void update();

    void populate();

    void signalsSlots();

    void check();

    void add();

    void select();

    void going();

    vector<string> split(string line, char delim);

    void updateDate();

    void updateDecription();

    void popular();

private:
    Ui::GUI *ui;
    Service &serv;
    Person pers;
};


#endif //EVENT_PLANNER_GUI_H
