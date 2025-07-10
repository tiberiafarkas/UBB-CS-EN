//
// Created by teodo on 6/20/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"
#include <QMessageBox>
#include <sstream>
#include <QVBoxLayout>


GUI::GUI(Service &serv, Person pers, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), serv(serv), pers(pers) {
    ui->setupUi(this);

    this->setWindowTitle(QString::fromStdString(pers.getName()+" Latitude: ")+QString::number(pers.getLatitude())+" Longitude: "+QString::number(pers.getLongitude()));
    serv.addObserver(this);
    this->populate();
    this->signalsSlots();
}

GUI::~GUI() {
    delete ui;
}

void GUI::update() {
    this->ui->listWidget->clear();
    for(auto i:serv.getEvents())
    {
        QListWidgetItem *listItem = new QListWidgetItem (QString::fromStdString(i.getOrganiser()+","+i.getName())+","+QString::number(i.getLatitude())+","+QString::number(i.getLongitude())+","+QString::number(i.getDate()));
        if(i.getOrganiser() == pers.getName())
            listItem->setBackground(Qt::green);
        this->ui->listWidget->addItem(listItem);
    }
    connect(this->ui->listWidget, &QListWidget::itemClicked, this, &GUI::select);
}

void GUI::populate() {
    this->ui->listWidget->clear();
    for(auto i:serv.getEvents())
    {
        QListWidgetItem *listItem = new QListWidgetItem (QString::fromStdString(i.getOrganiser()+","+i.getName())+","+QString::number(i.getLatitude())+","+QString::number(i.getLongitude())+","+QString::number(i.getDate()));
        if(i.getOrganiser() == pers.getName())
            listItem->setBackground(Qt::green);
        this->ui->listWidget->addItem(listItem);
    }

}

void GUI::signalsSlots() {
    connect(this->ui->checkBox, &QCheckBox::clicked, this, &GUI::check);
    connect(this->ui->pushButtonAdd, &QPushButton::clicked, this, &GUI::add);
    connect(this->ui->listWidget, &QListWidget::itemClicked, this, &GUI::select);
    connect(this->ui->pushButton,&QPushButton::clicked, this, &GUI::going);
    connect(this->ui->pushButtonDateUpdate, &QPushButton::clicked, this, &GUI::updateDate);
    connect(this->ui->pushButtonDescriptionUpdate, &QPushButton::clicked, this, &GUI::updateDecription);
    connect(this->ui->pushButton_2, &QPushButton::clicked, this, &GUI::popular);
}

void GUI::check() {
    if(this->ui->checkBox->isChecked())
    {
        vector<Event> arr = serv.getTheClosestEvents(pers);
        this->ui->listWidget->clear();
        for(auto i:arr)
        {
            QListWidgetItem *listItem = new QListWidgetItem (QString::fromStdString(i.getOrganiser()+","+i.getName())+QString::number(i.getLatitude())+","+QString::number(i.getLongitude())+","+QString::number(i.getDate()));
            if(i.getOrganiser() == pers.getName())
                listItem->setBackground(Qt::green);
            this->ui->listWidget->addItem(listItem);
        }
    }
    else
        this->populate();
}

void GUI::add() {
    if(pers.getStatus() == false)
    {
        QMessageBox::warning(this,"Error!", "You are not an organiser! You can't add an event!");
    }
    else
    {
        string organiser = pers.getName();
        string name = this->ui->lineEditName->text().toStdString();
        string descr = this->ui->lineEditDescr->text().toStdString();
        int lat = this->ui->lineEditLati->text().toFloat();
        int longg = this->ui->lineEditLong->text().toFloat();
        int date = this->ui->lineEditDate->text().toInt();

        vector<Person> pers;

        Event ev = Event(organiser,name,descr,lat,longg,date,pers);
        int sem = serv.addEvent(ev);
        this->populate();
        serv.notifyAllObservables();
        if(sem==-1)
            QMessageBox::warning(this,"Error!", "The same event!");
    }


}

void GUI::select() {
    this->ui->listWidget_2->clear();
    if(pers.getStatus() == false) // e participant
    {
        auto event = this->ui->listWidget->selectedItems()[0];
        string eventData = event->text().toStdString();
        vector<string> eventItems = this->split(eventData, ',');
        Event& ev = serv.getEvent(eventItems[1], stoi(eventItems[3]), stoi(eventItems[2]));
        this->ui->listWidget_2->addItem(QString::fromStdString(ev.getDescription()));

    }
    else   // e organizator
    {
        auto event = this->ui->listWidget->selectedItems()[0];
        string eventData = event->text().toStdString();
        vector<string> eventItems = this->split(eventData, ',');
        Event ev = serv.getEvent(eventItems[1], stoi(eventItems[3]), stoi(eventItems[2]));
        auto item=ev.getDescription();
        this->ui->listWidget_2->addItem(QString::fromStdString(item));
        for(auto i:ev.getParticipants())
        {
            item=(i.getName());
            this->ui->listWidget_2->addItem(QString::fromStdString(item));
        }

    }

}

void GUI::going() {
    this->ui->listWidget_2->clear();
    if(pers.getStatus() == false) // e participant
    {
        auto event = this->ui->listWidget->selectedItems()[0];
        string eventData = event->text().toStdString();
        vector<string> eventItems = this->split(eventData, ',');
        Event &ev = serv.getEvent(eventItems[1], stoi(eventItems[3]), stoi(eventItems[2]));
        this->ui->listWidget_2->addItem(QString::fromStdString(ev.getDescription()));

        int sem = serv.addParticipant(ev, pers);
        if(sem == -1)
            QMessageBox::warning(this,"Button disabled!", "Button disabled! The event is already in the list!");
        this->populate();

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

void GUI::updateDate() {
    if(pers.getStatus() == true)
    {
        auto event = this->ui->listWidget->selectedItems()[0];
        string eventData = event->text().toStdString();
        vector<string> eventItems = this->split(eventData, ',');
        Event &ev = serv.getEvent(eventItems[1], stoi(eventItems[3]), stoi(eventItems[2]));

        int newDate = this->ui->lineEditDatUpadate->text().toInt();
        ev.setDate(newDate);
        serv.notifyAllObservables();

    }
    else
        QMessageBox::warning(this,"Error!", "You are not an organiser!");

}

void GUI::updateDecription() {
    if(pers.getStatus() == true)
    {
        auto event = this->ui->listWidget->selectedItems()[0];
        string eventData = event->text().toStdString();
        vector<string> eventItems = this->split(eventData, ',');
        Event &ev = serv.getEvent(eventItems[1], stoi(eventItems[3]), stoi(eventItems[2]));

        string newDescr = this->ui->lineDescrUpdate->text().toStdString();
        ev.setDescription(newDescr);
        serv.notifyAllObservables();

    }
    else
        QMessageBox::warning(this,"Error!", "You are not an organiser!");

}

void GUI::popular() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Popular Items");

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *label = new QLabel("Here are the popular items!", dialog);
    QPushButton *closeButton = new QPushButton("Close", dialog);

    //////
    QListWidget *list1 = new QListWidget();
    vector<Event> arr = serv.getMostPopulars();
    for(auto i:arr)
    {
        QListWidgetItem *listItem = new QListWidgetItem (QString::fromStdString(i.getOrganiser()+","+i.getName())+","+QString::number(i.getLatitude())+","+QString::number(i.getLongitude())+","+QString::number(i.getDate()));
        list1->addItem(listItem);
    }


    layout->addWidget(reinterpret_cast<QWidget *>(list1));
    //////

    layout->addWidget(label);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

    dialog->setLayout(layout);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    dialog->exec();

}
