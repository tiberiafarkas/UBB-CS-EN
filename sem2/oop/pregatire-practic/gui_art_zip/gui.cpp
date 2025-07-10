//
// Created by teodo on 6/19/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"
#include <QMessageBox>
#include <sstream>
#include <algorithm>

GUI::GUI(Service &serv, User user,QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), serv(serv), user(user) {
    ui->setupUi(this);

    this->setWindowTitle(QString::fromStdString(user.getName()));
    serv.addObserver(this);

    this->populate();
    this->signalsSlots();
}

GUI::~GUI() {
    delete ui;
}

void GUI::populate() {

    this->putInComboBox();
    this->ui->listWidget->clear();
    for(auto i:serv.getItems())
    {
        this->ui->listWidget->addItem(QString::fromStdString(i.getName())+","+QString::fromStdString(i.getCategory())+","+QString::number(i.getPrice()));
    }
    serv.notifyAllObservables();

}

void GUI::signalsSlots() {

    connect(this->ui->comboBox, &QComboBox::currentIndexChanged, this, &GUI::filter);
    connect(this->ui->pushButtonAdd, &QPushButton::clicked, this, &GUI::add);
    connect(this->ui->listWidget, &QListWidget::itemClicked, this, &GUI::showOffers);
    connect(this->ui->pushButton, &QPushButton::clicked, this, &GUI::bid);

}

void GUI::update() {
    this->ui->listWidget->clear();
    auto items = serv.getItems();
    if(category!="all")
        items = serv.sortByCategory(category);
    for(auto i:items)
    {
        this->ui->listWidget->addItem(QString::fromStdString(i.getName())+","+QString::fromStdString(i.getCategory())+","+QString::number(i.getPrice()));
    }
}

void GUI::filter() {
    QString categ = this->ui->comboBox->currentText();
    category = categ.toStdString();
   // vector<Item> arr = serv.sortByCategory(category);
//
//    this->ui->listWidget->clear();
//    for(auto i:arr)
//    {
//            this->ui->listWidget->addItem(QString::fromStdString(i.getName())+","+QString::fromStdString(i.getCategory())+","+QString::number(i.getPrice()));
//    }
    serv.notifyAllObservables();


}

void GUI::putInComboBox() {
    this->ui->comboBox->clear();
    vector<string> categories;
    this->ui->comboBox->addItem(QString::fromStdString("all"));

    for(auto i:serv.getItems())
    {
        int sem=0;
        for(auto j:categories)
        {
            if(j == i.getCategory())
                sem=1;
        }
        if(sem==0)
        {
            this->ui->comboBox->addItem(QString::fromStdString(i.getCategory()));
            categories.push_back(i.getCategory());
        }
    }

}

void GUI::add() {
    QString nam=this->ui->lineEditName->text();
    string name = nam.toStdString();

    QString cat=this->ui->lineEditCategory->text();
    string cateogory = cat.toStdString();

    QString pri=this->ui->qLineEditPrice->text();
    int price = pri.toInt();

    vector<tuple<int,int,int>> list;

    Item item = Item(name, category, price, list);
    if(name=="" || price<=0)
        QMessageBox::warning(this, "Error", "Invalid data!");
    else
    {
        serv.addItem(item);
        this->update();
    }
}

void GUI::showOffers() {
    auto str = this->ui->listWidget->currentItem();
    QString string1 = str->text();
    string items = string1.toStdString();

    vector<string> all = split(items, ',');
    this->ui->listWidget_2->clear();
    for(auto i:serv.getItems())
    {
        if(i.getName() == all[0])
        {
            vector<tuple<int,int,int>> list = i.getList();
            sort(list.begin(), list.end(), compare1);
            for(auto j:list)
            this->ui->listWidget_2->addItem(QString::number(get<0>(j))+ "," + QString::number(get<1>(j))+ ","+QString::number(get<2>(j)));
        }

    }

}

vector<string> GUI::split(string line, char delim) {
    vector<string> tokens;
    stringstream ss{line};
    string current;
    while (getline(ss, current, delim))
    {
        tokens.push_back(current);
    }
    return tokens;
}

bool GUI::compare1(tuple<int, int, int> a, tuple<int, int, int> b) {
    return get<1>(a)<get<1>(b);
}

void GUI::bid() {
    if(user.getType()=="collector") {
        QString line = this->ui->qLineEditBid->text();

        int offer = line.toInt();

        if (offer < 0)
            QMessageBox::warning(this, "Error!", "Negative sum!");
        else {
            auto ite = this->ui->listWidget->currentItem();
            QString items = ite->text();
            string bidItem = items.toStdString();
            vector<string> things = split(bidItem, ',');
            for (auto &&i: serv.getItems()) {
                if (i.getName() == things[0]) {
                    i.setPrice(offer);
                    vector<tuple<int, int, int>> list = i.getList();
                    list.push_back(make_tuple(user.getId(), 2024, offer));
                    i.setList(list);
                    serv.notifyAllObservables();
                }
            }
            this->update();
        }
    }
    else
        QMessageBox::warning(this, "Error!", "You are not a collector!");

}

