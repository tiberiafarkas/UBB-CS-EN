#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Service.h"

class ViewStarsWindow : public QWidget {
    Q_OBJECT
private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    Service& service;
    std::string constellation;
    Star selectedStar;
public:
    ViewStarsWindow(Service& service, std::string constellation, Star selectedStar, QWidget* parent = nullptr);
    void setup();
};
