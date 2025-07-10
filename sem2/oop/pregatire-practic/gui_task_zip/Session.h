
#pragma once
#include "Subject.h"
#include "Person.h"
#include "Issue.h"
class Session : public Subject{
private:
    std::vector <Person> persons;
    std::vector <Issue> issues;
    std::string personsFilePath, issuesFilePath;
public:
    Session()
    {
        this->personsFilePath = "persons.txt";
        this->issuesFilePath = "issues.txt";
        this->loadRepo();
    }
    Session &operator=(const Session &other);
    ~Session() { this->saveIssues(); };
    std::vector <Person> &getPersons() { return this->persons; };
    std::vector <Issue> &getIssues() { return this->issues; };
    void loadRepo();
    void saveIssues();
    bool checkIfIssueExists(const std::string &description);
    void addIssue(const std::string &description, bool isOpen, const std::string &nameReporter, const std::string &nameSolver);
    void removeIssue(int position);
    void resolveIssue(int position, const std::string &nameSolver);
};


