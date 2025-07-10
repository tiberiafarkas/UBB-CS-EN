#include "UserView.h"
#include <QMessageBox>


UserView::UserView(User& user, Service& service, QWidget *parent)
	: QMainWindow(parent), user{ user }, service{ service } 
{
	ui.setupUi(this);

	connectSignalAndSlots();

	service.addObserver(this);

	this->setWindowTitle(QString::fromStdString(user.getName())); 

	update();
}

UserView::~UserView()
{
	service.removeObserver(this); 
}

void UserView::update()
{
	ui.listWithData->clear(); 
	for (auto& question : service.getAnswers()) 
	{
		ui.listWithData->addItem(QString::fromStdString(question.toString())); 
	}
}

void UserView::connectSignalAndSlots()
{
	QObject::connect(ui.listWithData, &QListWidget::itemSelectionChanged, [&]() {
		int selectedIndex = ui.listWithData->currentIndex().row();   
		if (selectedIndex < 0) 
			return; 
		
		Answer answer = service.getAnswers()[selectedIndex]; 

		if(answer.getUserName() == user.getName())  
		{
			ui.spinBox->setEnabled(false);
			return;
		}
		ui.spinBox->setEnabled(true);

		ui.spinBox->setValue(answer.getNrOfVotes());  

		});

	QObject::connect(ui.spinBox, &QSpinBox::valueChanged, [&]() {
		int selectedIndex = ui.listWithData->currentIndex().row(); 
		qDebug() << selectedIndex;
		if (selectedIndex < 0)
			return;

		service.updateAnswer(selectedIndex, ui.spinBox->value());

		});
}