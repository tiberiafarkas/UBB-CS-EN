//
// Created by Dragos on 6/30/2022.
//

#ifndef CODE_REVISION_GUI_H
#define CODE_REVISION_GUI_H

#include <QWidget>
#include "PRepo.h"
#include "Service.h"
#include "Observer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget, public Observer{
Q_OBJECT

public:
    explicit gui(Service& service, Programmer& programmer, QWidget *parent = Q_NULLPTR);

    ~gui() override;

    void connect_signals_and_sluts();

    void add_source_file();
    void select_source_file();
    void revise();

    void update() override;

private:
    Ui::gui *ui;
    Service& srv;
    Programmer& programmer;
};


#endif //CODE_REVISION_GUI_H
