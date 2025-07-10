#pragma once

#include <vector>
#include "driver.h"
#include "subject.h"
#include "report.h"


class Repository : public Subject
{
private:
	std::vector<Driver> drivers;
	std::vector<Report> reports;
public:
	Repository();
	~Repository();
	std::vector<Driver>& getDrivers();
	std::vector<Report> getReports();
	//void addDriver(Driver driver);
	void addReport(Report report);
	void updateDriver(int index);
	void updateReport(int index);
	
	void readDriversFromFile();
	void readReportsFromFile();

	void writeDriversToFile();
	void writeReportsToFile();

};