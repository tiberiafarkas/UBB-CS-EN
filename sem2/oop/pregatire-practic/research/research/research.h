#pragma once

#include <QtWidgets/QWidget>
#include "ui_research.h"
#include "research.h"
#include "service.h"
#include "ideas.h"
#include "tableModelView.h"

class research : public QWidget
{
    Q_OBJECT

public:
    research(Researcher& researcher, Service& service, IdeasTableView* model, QWidget *parent = nullptr);
    ~research();

public slots:
    void addIdea();
    void acceptIdea();
    void updateIdea();
    //void save();

private:
    Ui::researchClass ui;
	Researcher& researcher;
    Service& service;
    IdeasTableView* model;
    vector<Ideea> changedIdeas;
};

