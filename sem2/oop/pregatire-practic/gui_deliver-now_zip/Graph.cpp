#include "Graph.h"

Graph::Graph(Service& service, QWidget* parent)
    :QWidget{ parent }, service{ service }
{
    this->setFixedSize(800, 600);
    this->setWindowTitle("Map");
    service.attach(this);
}

Graph::~Graph()
{
    service.detach(this);
}

void Graph::update()
{
    this->repaint();
}

void Graph::paintEvent(QPaintEvent* _event)
{
    (void)_event;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    for (auto& package : this->service.getAllPackages())
    {
        if (package.getStatus())
            continue;
        auto loc = package.getLocation();
        painter.drawEllipse(loc.x, loc.y, 10, 10);
    }
}
