#include "ViewStarsWindow.h"

#include <QVBoxLayout>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

ViewStarsWindow::ViewStarsWindow(Service& service, std::string constellation, Star selectedStar, QWidget* parent)
    : QWidget(parent), service(service), constellation(std::move(constellation)), selectedStar(std::move(selectedStar)) {
    this->setup();
}

void ViewStarsWindow::setup() {
    auto* layout = new QVBoxLayout(this);
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    layout->addWidget(view);

    // Get stars in the selected constellation
    auto stars = service.getStars();
    for (const auto& star : stars) {
        if (star.getConstellation() == constellation) {
            QBrush brush = (star.getName() == selectedStar.getName()) ? QBrush(Qt::red) : QBrush(Qt::black);
            auto* item = scene->addEllipse(star.getRa(), star.getDec(), star.getDiameter(), star.getDiameter(), QPen(), brush);
            item->setToolTip(QString::fromStdString(star.getName()));
        }
    }

    this->setLayout(layout);
    this->setWindowTitle(QString::fromStdString("Stars in " + constellation));
}
