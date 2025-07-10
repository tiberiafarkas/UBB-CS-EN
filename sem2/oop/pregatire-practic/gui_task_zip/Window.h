#pragma once
#include "Observer.h"
#include "Session.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class Window : public QWidget, public Observer {
private:
    Session &session;
    Person &currentPerson;
    QListWidget *issuesList;
    QPushButton *addIssueButton, *resolveIssueButton, *removeIssueButton;
    QLineEdit *descriptionInput;
public:
    Window(Session &session, Person &currentPerson, QWidget *parent = Q_NULLPTR);
    ~Window() override = default;;
    void update() const override;
public slots:
    void removeIssue();
    void addIssue();
    void resolveIssue();
    void updateResolveButton();
};


