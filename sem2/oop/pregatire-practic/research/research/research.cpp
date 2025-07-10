#include "research.h"
#include <QTextEdit>

research::research(Researcher& researcher, Service& service, IdeasTableView* model, QWidget *parent) : 
    researcher(researcher), service(service), model(model), QWidget(parent)
{
    ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(researcher.getName() + researcher.getPosition()));

	ui.tableView->setModel(model);

	if (researcher.getPosition() != "senior") {
		ui.acceptIdea->hide();
	}

	connect(ui.addIdea, &QPushButton::clicked, this, &research::addIdea);
	connect(ui.acceptIdea, &QPushButton::clicked, this, &research::acceptIdea);
	connect(ui.develop, &QPushButton::clicked, this, &research::updateIdea);
}

void research::addIdea() {
	string title = ui.title->text().toStdString();
	string description = ui.description->text().toStdString();
	int duration = ui.duration->text().toInt();

	Ideea idea{ title, description, "proposed", researcher.getName(), duration };

	model->addIdea(idea);
}

void research::acceptIdea() {
	int index = ui.tableView->currentIndex().row();
	model->reviseIdea(index);
}

void research::updateIdea() {
	vector<Ideea> ideas = model->acceptedIdeas(researcher);
	for (auto idea : ideas) {
		QWidget* widget = new QWidget();
		QLayout* layout = new QVBoxLayout();
		QTextEdit* textEdit = new QTextEdit(QString::fromStdString(idea.getDescription()));
		textEdit->setObjectName("edit");
		layout->addWidget(textEdit);
		widget->setLayout(layout);
		widget->show();
	}
}

research::~research()
{}

