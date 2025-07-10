//
// Created by Dragos on 6/30/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_statistics.h" resolved

#include "statistics.h"
#include "ui_statistics.h"


statistics::statistics(Service& srv, PRepo& prepo, QWidget *parent) :
        QWidget(parent), ui(new Ui::statistics), prepo(prepo), srv(srv) {
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("Statistics"));
    srv.addObserver(this);
    update();
}

statistics::~statistics() {
    delete ui;
}

void statistics::update() {

}

