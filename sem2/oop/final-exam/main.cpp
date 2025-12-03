#include "gui.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include <QDebug>
#include <sstream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	Service service;

	for (auto& dep : service.getDepartments()) {
		qDebug() << dep.getName() << dep.getDescription();
		for (auto& v : service.getVolunteers()) {
				qDebug() << v.getName() << v.getEmail() << v.getListOfInterests() << v.getDepartment();
			if (v.getDepartment() == dep.getName()) {
				dep.getVolunteers().push_back(v);
			}
			if (v.getDepartment() == "unassigned") {
				double score = 0;
				double interestWordsInDepDescription = 0;
				for (auto& interest : v.getListOfInterests()) {
					if (dep.getDescription().find(interest) != std::string::npos) {
						interestWordsInDepDescription++;
					}
				}
				double totalDescriptionWords = 0;
				std::istringstream iss(dep.getDescription());
				std::string word;
				while (iss >> word) {
					totalDescriptionWords++;
				}
				if (totalDescriptionWords > 0) {
					score = interestWordsInDepDescription / totalDescriptionWords;
				}
				v.setScore(score);
			}
		}
		gui* window = new gui(dep, service);
		window->show();
	}

	// Create the main window
	Department dep("Main", "Main Department");
	dep.setMainWindow(true);
	gui* mainWindow = new gui(dep, service);
	//mainWindow->show();


    return app.exec();
}
