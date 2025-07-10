//
// Created by Dragos on 6/30/2022.
//

#ifndef CODE_REVISION_STATISTICS_H
#define CODE_REVISION_STATISTICS_H

#include <QWidget>
#include "Observer.h"
#include "PRepo.h"
#include "Service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class statistics; }
QT_END_NAMESPACE

class statistics : public QWidget, public Observer{
Q_OBJECT

public:
    explicit statistics(Service& srv, PRepo& prepo, QWidget *parent = nullptr);

    ~statistics() override;

    void update() override;

private:
    Ui::statistics *ui;
    PRepo& prepo;
    Service& srv;
};


#endif //CODE_REVISION_STATISTICS_H
