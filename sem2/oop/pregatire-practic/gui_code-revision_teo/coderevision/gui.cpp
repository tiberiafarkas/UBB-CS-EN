//
// Created by Dragos on 6/30/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"
#include "QMessageBox"

vector<string> tokenize4(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

gui::gui(Service& service, Programmer& programmer, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), srv(service), programmer(programmer) {
    ui->setupUi(this);
    update();
    this->setWindowTitle(QString::fromStdString(programmer.getName()));
    connect_signals_and_sluts();
    srv.addObserver(this);
    ui->buttonRevise->setDisabled(true);
}

gui::~gui() {
    delete ui;
}

void gui::connect_signals_and_sluts() {
    QObject::connect(this->ui->buttonAddSourceFile, &QPushButton::clicked, this, &gui::add_source_file);
    QObject::connect(this->ui->listWidget, &QListWidget::itemClicked, this, &gui::select_source_file);
    QObject::connect(this->ui->buttonRevise, &QPushButton::clicked, this, &gui::revise);
}

void gui::add_source_file() {
    string name = ui->lineName->text().toStdString();
    if(name == ""){
        QMessageBox box;
        box.setText(QString::fromStdString("name can't be empty"));
        box.exec();
    }
    else{
        if(!srv.search_sf(name)){
            QMessageBox box;
            box.setText(QString::fromStdString("source file with this name already exists"));
            box.exec();
        }
        else{
            srv.add_sf(name, programmer.getName());
        }
    }
}

void gui::update() {
    ui->listWidget->clear();
    for(auto& sf: srv.sorted_by_name()){
        string text = sf.getName() + ',' + sf.getStatus() + ',' + sf.getCreator() + ',' + sf.getReviewer();
        ui->listWidget->addItem(QString::fromStdString(text));
        if(!sf.is_revised()){
            QFont font;
            font.setBold(true);
            ui->listWidget->item(ui->listWidget->count()-1)->setFont(font);
        }
    }
    ui->Revised->setText(QString::fromStdString(to_string(programmer.getRevised())));
    ui->MustRevise->setText(QString::fromStdString(to_string(programmer.getMustRevise())));
}

void gui::select_source_file() {
    auto item = ui->listWidget->selectedItems()[0];
    string line = item->text().toStdString();
    vector<string> tokens = tokenize4(line,',');
    if(tokens[1] == "revised" || tokens[2] == programmer.getName()){
        ui->buttonRevise->setDisabled(true);
    }
    else{
        ui->buttonRevise->setDisabled(false);
    }
}

void gui::revise() {
    auto item = ui->listWidget->selectedItems()[0];
    string line = item->text().toStdString();
    vector<string> tokens = tokenize4(line,',');
    programmer.setRevised(programmer.getRevised() + 1);
    programmer.setMustRevise(programmer.getMustRevise() -1);
    srv.revise(tokens[0], programmer.getName());
}

