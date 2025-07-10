#include "mainWindow.h"

MainWindow::MainWindow(Service& service, QWidget* parent)
	: QWidget(parent), service(service)
{ 
	this->setWindowTitle("Movie Application");
	this->setMinimumSize(1000, 600);
	this->setStyleSheet("background-color: #985fc2;"); // Set a light background color

	this->chooseFileType();
}

void MainWindow::chooseFileType() {
	//choose between csv, html and file repo when it comes to watchlist

	QVBoxLayout* layout = new QVBoxLayout(this);
	this->setWindowTitle("Choose File Type");

	QPushButton* csvButton = new QPushButton("CSV", this);
	csvButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 20px; padding: 10px;");
	csvButton->setMinimumWidth(200); // Set minimum width for the button
	csvButton->setMaximumWidth(400); // Set maximum width for the button


	QPushButton* htmlButton = new QPushButton("HTML", this);
	htmlButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 20px; padding: 10px;");
	htmlButton->setMinimumWidth(200); // Set minimum width for the button
	htmlButton->setMaximumWidth(400); // Set maximum width for the button
	
	QPushButton* fileButton = new QPushButton("File", this);
	fileButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 20px; padding: 10px;");
	fileButton->setMinimumWidth(200); // Set minimum width for the button
	fileButton->setMaximumWidth(400); // Set maximum width for the button

	layout->addWidget(csvButton, 0, Qt::AlignCenter);
	layout->addWidget(htmlButton, 0, Qt::AlignCenter);
	layout->addWidget(fileButton, 0, Qt::AlignCenter);

	connect(csvButton, &QPushButton::clicked, this, [this]() {
		this->service.setTypeOfRepository("1");
		this->chooseMode();
		});

	connect(htmlButton, &QPushButton::clicked, this, [this]() {
		this->service.setTypeOfRepository("2");
		this->chooseMode();
		});

	connect(fileButton, &QPushButton::clicked, this, [this]() {
		this->service.setTypeOfRepository("3");
		this->chooseMode();
		});

	this->setLayout(layout);
}

void MainWindow::chooseMode() {
	QLayout* oldLayout = this->layout();
	if (oldLayout != nullptr) {
		QLayoutItem* item;
		while ((item = oldLayout->takeAt(0)) != nullptr) {
			if (QWidget* w = item->widget())
				w->deleteLater();
			delete item;
		}
		delete oldLayout;
	}
	QVBoxLayout* layout = new QVBoxLayout(this);

	this->adminButton = new QPushButton("Admin Mode", this);
	// Set the button style
	this->adminButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 20px; padding: 10px;");
	this->adminButton->setMinimumWidth(200); // Set minimum width for the button
	this->adminButton->setMaximumWidth(400);

	this->userButton = new QPushButton("User Mode", this);
	// Set the button style
	this->userButton->setStyleSheet("background-color: #fafa98; color: black; font-size: 20px; padding: 10px;");
	this->userButton->setMinimumWidth(200); 
	this->userButton->setMaximumWidth(400);


	layout->addWidget(this->adminButton, 0, Qt::AlignCenter);
	layout->addWidget(this->userButton, 0, Qt::AlignCenter);

	connect(this->adminButton, &QPushButton::clicked, this, &MainWindow::showAdminWindow);
	connect(this->userButton, &QPushButton::clicked, this, &MainWindow::showUserWindow);

	this->adminWidget = new AdminWidget(this->service, nullptr);
	this->userWidget = new UserWidget(this->service, nullptr);
	this->adminWidget->setWindowTitle("Admin Mode");
	this->userWidget->setWindowTitle("User Mode");

	connect(this->userWidget, &UserWidget::backButtonClicked, this, &MainWindow::handleBack);
	connect(this->adminWidget, &AdminWidget::backButtonClicked, this, &MainWindow::handleBack);
}

MainWindow::~MainWindow()
{
	delete this->adminWidget;
	this->adminWidget = nullptr;

	delete this->userWidget;
	this->userWidget = nullptr;
}

void MainWindow::showAdminWindow()
{
	this->hide();
	this->adminWidget->show();
	//this->close();
}

void MainWindow::showUserWindow()
{
	this->hide();
	this->userWidget->show();
	//this->close();
}

void MainWindow::handleBack()
{
	this->adminWidget->hide();
	this->userWidget->hide();
	this->show();
}
