//
// Created by teodo on 6/19/2024.
//

#ifndef ART_AUCTION_PLATFORM_GUI_H
#define ART_AUCTION_PLATFORM_GUI_H

#include <QWidget>
#include "Service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget, public Observer {
Q_OBJECT

public:
    explicit GUI(Service &serv, User user, QWidget *parent = nullptr);

    ~GUI() override;

    void populate();

    void putInComboBox();

    void update() override;

    void signalsSlots();

    void filter();

    void add();

    void showOffers();

    vector<string > split(string line, char delim);

    static bool compare1(tuple<int,int,int> a, tuple<int,int,int> b);

    void bid();

private:
    Ui::GUI *ui;
    string category="all";
    Service &serv;
    User user;
};


#endif //ART_AUCTION_PLATFORM_GUI_H
