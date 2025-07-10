#include "MainWindow.h"

MainWindow::MainWindow(Service& service, User user) : service{ service }, user{ user }, ui{ new Ui::MainWindowClass }
{
	ui->setupUi(this);
	this->setWindowTitle("Auction House");
	this->populateList();
	this->service.addObserver(this);
	connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::comboBoxChanged);
	connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addButtonClicked);
	connect(ui->bidButton, &QPushButton::clicked, this, &MainWindow::bidUser);
}


MainWindow::~MainWindow()
{
    delete ui;
}

