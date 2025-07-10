#include "WriterView.h"
#include <qmessagebox.h>
#include <fstream>

WriterView::WriterView(Writer& writer, Repository& repository, IdeaTabelModel* ideaTabelModel, QWidget *parent)
	: QMainWindow(parent), repository{ repository }, ideaTabelModel{ ideaTabelModel }, writer{ writer }
{
	ui.setupUi(this);

	connectSignalsAndSlots();

	ui.tableWithData->setModel(ideaTabelModel);

	this->setWindowTitle(QString::fromStdString(writer.getName() + " is a " + writer.getExpertise()));

	ui.developButton->setEnabled(false);

	for(auto& idea : repository.getIdeas())
		if (idea.getCreator() == writer.getName() && idea.getStatus() == "accepted")
		{
			ui.developButton->setEnabled(true);
			break;
		}
}

WriterView::~WriterView()
{}

void WriterView::connectSignalsAndSlots()
{
	QObject::connect(ui.addButton, &QPushButton::clicked, [&]() {

		std::string description = ui.descriptionLineEdit->text().toStdString(); 
		std::string status = "proposed";
		std::string creator = writer.getName(); 
		int act = ui.actLineEdit->text().toInt();

		Idea idea{ description, status, creator, act }; 
		try
		{
			ideaTabelModel->addIdea(idea);
		}
		catch (std::exception& e)
		{
			QMessageBox::critical(this, "Error", e.what());
		}

		});

	QObject::connect(ui.saveButton, &QPushButton::clicked, [&]() {
		
		std::ofstream file("result.txt");

		file << "Act 1\n";

		for (auto& idea : repository.getIdeas())
		{
			if(idea.getAct() == 1 && idea.getStatus() == "accepted")
				file << idea.getDescription() << " (" << idea.getCreator() << ")\n";
		}

		file << "\n\nAct 2\n";

		for (auto& idea : repository.getIdeas()) 
		{
			if (idea.getAct() == 2 && idea.getStatus() == "accepted")
				file << idea.getDescription() << " (" << idea.getCreator() << ")\n"; 
		}

		file << "\n\nAct 3\n";

		for (auto& idea : repository.getIdeas())
		{
			if (idea.getAct() == 3 && idea.getStatus() == "accepted")
				file << idea.getDescription() << " (" << idea.getCreator() << ")\n"; 
		}
		
		});
	
}
