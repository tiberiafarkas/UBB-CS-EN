#include "gui_microbial.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "Service.h"
#include "bacteriaModels.h"
#include "gui_biologist.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    Repository repository("biologist.txt", "bacteria.txt");


    auto* model = new bacteriaModels(repository);

    Service service(repository);

    for (const auto& biologist : service.getBiologists()) {

        auto* window = new BiologistWindow(biologist, service, model);
        window->show();
    }

    return QApplication::exec();
}