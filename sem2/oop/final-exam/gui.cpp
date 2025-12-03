#include "gui.h"
#include <algorithm>
#include <QMessageBox>

gui::gui(Department& dep, Service& serv, QWidget *parent): dep(dep), service(serv), QWidget(parent)
{
    ui.setupUi(this);
	if (!dep.isMainWindow()) {
		service.addObserver(this);
		setWindowTitle(QString::fromStdString(dep.getName()));

		ui.description->setText(QString::fromStdString(dep.getDescription()));

		populateList();
		populateDepartmentList();
		updateSuitableVolunteersList();
		connect(ui.addV, &QPushButton::clicked, this, &gui::addVolunteer);
		connect(ui.unassignedVolunteer, &QListWidget::itemClicked, this, &gui::assignVolunteer);
	}
	else {
		QWidget* mainWindow = new QWidget(parent);
		mainWindow->setWindowTitle(QString::fromStdString("MainWindow"));
		
		vector<Department> departments = service.getDepartments();
		sort(departments.begin(), departments.end(), [](Department& a, Department& b) {
			return a.getVolunteers().size() > b.getVolunteers().size();
			});
		
		// Create a list widget to display departments and volunteer counts
		QListWidget* departmentListWidget = new QListWidget(mainWindow);
		
		for (auto& d : departments) {
			QString itemText = QString::fromStdString(
				d.getName() + " | Volunteers: " + std::to_string(d.getVolunteers().size())
			);
			departmentListWidget->addItem(itemText);
		}
		
		// Layout to show the list widget
		QVBoxLayout* layout = new QVBoxLayout(mainWindow);
		layout->addWidget(departmentListWidget);
		mainWindow->setLayout(layout);
		mainWindow->show();
	}
}

//void gui::MainWindow() {
//	if (!mainWindow) {
//		mainWindow = new QWidget(this);
//		mainWindow->setWindowTitle(QString::fromStdString("MainWindow"));
//		departmentListWidget = new QListWidget(mainWindow);
//		QVBoxLayout* layout = new QVBoxLayout(mainWindow);
//		layout->addWidget(departmentListWidget);
//		mainWindow->setLayout(layout);
//		mainWindow->show();
//	}
//	updateMainWindowList();
//}
//
//void gui::updateMainWindowList() {
//	if (!departmentListWidget) return;
//	departmentListWidget->clear();
//	auto departments = service.getDepartments();
//	std::sort(departments.begin(), departments.end(), [](Department& a, Department& b) {
//		return a.getVolunteers().size() > b.getVolunteers().size();
//		});
//	for (auto& d : departments) {
//		QString itemText = QString::fromStdString(
//			d.getName() + " | Volunteers: " + std::to_string(d.getVolunteers().size())
//		);
//		departmentListWidget->addItem(itemText);
//	}
//}


void gui::populateDepartmentList()
{
	ui.volunteer->clear();
	vector<Volunteer> volunteers = service.getDepartmentVolunteers(dep);

	sort(volunteers.begin(), volunteers.end(), [](Volunteer& a, Volunteer& b) {
		return a.getName() < b.getName();
		});

	for (auto& v : volunteers) {
		ui.volunteer->addItem(QString::fromStdString(v.getName() + " | " + v.getEmail()));
	}
}

void gui::populateList()
{
	ui.unassignedVolunteer->clear();
	auto volunteers = service.getVolunteers();
	for (auto& v : volunteers) {
		if (v.getDepartment() == "unassigned") {
			ui.unassignedVolunteer->addItem(QString::fromStdString(v.getName() + " | " + v.getEmail()));
		}
	}
}

void gui::addVolunteer() {
	if (ui.name->text().isEmpty() || ui.email->text().isEmpty()) {
		QMessageBox::warning(this, "Warning", "Please fill in all fields.");
		return;
	}
	std::string name = ui.name->text().toStdString();
	std::string email = ui.email->text().toStdString();
	vector<std::string> interests = { ui.interest->text().toStdString() };
	/*for (int i = 0; i < ui.interest->count(); ++i) {
		interests.push_back(ui.interest->item(i)->text().toStdString());
	}*/
	Volunteer v(name, email, interests, "unassigned");
	service.addVolunteer(v);
	service.save();
	//update();
	populateList();
	populateDepartmentList();
	service.notifyAllObservers();
}


void gui::assignVolunteer() {
	QListWidgetItem* currentItem = ui.unassignedVolunteer->currentItem();
	if (!currentItem) {
		QMessageBox::warning(this, "Warning", "No volunteer selected.");
		return;
	}

	std::string selectedVolunteer = currentItem->text().toStdString();
	auto pos = selectedVolunteer.find('|');
	if (pos == std::string::npos) {
		QMessageBox::warning(this, "Warning", "Invalid volunteer format.");
		return;
	}
	std::string name = selectedVolunteer.substr(0, pos);
	// Trim whitespace if needed
	name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);

	Volunteer* v = nullptr;
	for (auto& vol : service.getVolunteers()) {
		if (vol.getName() == name) {
			v = &vol;
			break;
		}
	}
	if (!v) {
		QMessageBox::warning(this, "Warning", "Selected volunteer not found.");
		return;
	}
	std::string depart = dep.getName();
	v->setDepartment(depart);
	service.updateVolunteer(*v);
	dep.getVolunteers().push_back(*v); // Add volunteer to the department's list
	service.save();
	service.notifyAllObservers();
	populateList();
	populateDepartmentList();
}

void gui::updateSuitableVolunteersList() {
	ui.suitableList->clear();
	auto departments = service.getDepartments();

	for (auto& department : departments) {
		auto volunteers = service.getDepartmentVolunteers(department);

		std::sort(volunteers.begin(), volunteers.end(), [](Volunteer& a,Volunteer& b) {
			return a.getScore() > b.getScore();
			});

		ui.suitableList->addItem(QString::fromStdString(department.getName() + ":"));

		// Add up to 3 top volunteers
		int count = 0;
		for ( auto& v : volunteers) {
			if (count++ == 3) break;
			QString itemText = QString::fromStdString(
				"    " + v.getName() + " | Score: " + std::to_string(v.getScore())
			);
			ui.suitableList->addItem(itemText);
		}
		ui.suitableList->addItem(" ");
	}
}


void gui::update() {
	//service.notifyAllObservers();
	populateList();
	populateDepartmentList();
}

gui::~gui()
{}


