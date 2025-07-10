#include "MapView.h"
#include <QPainter>

MapView::MapView(Repository& repository, QWidget *parent)
	: QMainWindow(parent), repository{ repository }
{
	ui.setupUi(this);

	repository.addObserver(this);

	paintEvent(); 

	this->setWindowTitle("Map");

	this->setStyleSheet("background-color: #9fff80");
}

MapView::~MapView()
{
	repository.removeObserver(this); 
}

void MapView::update()
{
	paintEvent();
}

void MapView::paintEvent()
{
	QPainter painter{ this };
	for (auto& r : repository.getDrivers())
	{
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(QPen(Qt::black, 2));
		painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
		QRect rect(r.getLatitude(), r.getLongitude(), 5, 5); 
		painter.drawRect(rect); 
		painter.drawText(rect, Qt::AlignCenter, QString::fromStdString(r.getName() + " is at: " + std::to_string(r.getLatitude()) + " " + std::to_string(r.getLongitude())));
	}
}
