#include "repository.h"
#include <fstream>
#include <sstream>
#include <string>


Repository::Repository()
{
	readDriversFromFile(); 
	readReportsFromFile(); 
}

Repository::~Repository()
{
}

std::vector<Driver>& Repository::getDrivers()
{
	return drivers;
}

std::vector<Report> Repository::getReports()
{
	return reports;
}

void Repository::addReport(Report report)
{
	reports.push_back(report);
	notify(); 
}

void Repository::updateDriver(int index)
{
}

void Repository::updateReport(int index)
{
	if (reports[index].getValidated() < 2)
	{
		reports[index].increaseValidated();
		notify();
		return;
	}

	throw std::exception("Report already validated twice!");
}


void Repository::readDriversFromFile()
{
	std::ifstream file("d.txt"); 
	std::string line; 
	while (std::getline(file, line)) 
	{
		std::stringstream ss(line);
		std::string name, status, x;
		int latitude, longitude, score;

		while (ss >> x)
		{
			if (x == "|")
				break;
			name += x + " ";
		}
		name.pop_back();

		ss >> status >> x >> latitude >> longitude >> x >> score;

		Driver driver(name, status, latitude, longitude, score); 
		drivers.push_back(driver);   
	} 
}

void Repository::readReportsFromFile()
{
	std::ifstream file("r.txt");
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string reporter, description, x;
		int latitude, longitude;
		int validated;

		while (ss >> x)
		{
			if (x == "|")
				break;
			description += x + " ";
		}
		description.pop_back();

		while (ss >> x)
		{
			if (x == "|")
				break;
			reporter += x + " ";
		}
		reporter.pop_back();

		ss >> latitude >> longitude >> x >> validated;

		Report report(description, reporter, latitude, longitude, validated); 
		reports.push_back(report);  
	}
}

void Repository::writeDriversToFile()
{
	std::ofstream file("d.txt");
	for (auto driver : drivers)
	{
		file << driver.getName() << " | " << driver.getStatus() << " | " << driver.getLatitude() << " | " << driver.getLongitude() << " | " << driver.getScore() << "\n"; 
	} 
}

void Repository::writeReportsToFile()
{
	std::ofstream file("r.txt");
	for (auto report : reports)
	{
		file << report.getDescription() << " | " << report.getReporter() << " | " << report.getLatitude() << " " << report.getLongitude() << " | " << report.getValidated() << "\n";  
	}
}
