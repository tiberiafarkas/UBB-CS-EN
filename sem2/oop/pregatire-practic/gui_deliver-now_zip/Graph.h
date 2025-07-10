#include <QWidget>
#include <QPainter>
#include <vector>

#include "Service.h"
#include "Package.h"
#include "Courier.h"
#include "Observer.h"

class Graph : public QWidget, public Observer
{
    Q_OBJECT

public:
    Graph(Service& service, QWidget* parent = nullptr);
    ~Graph();
    void paintEvent(QPaintEvent* event) override;
private:
    Service& service;
    void update() override;
};
