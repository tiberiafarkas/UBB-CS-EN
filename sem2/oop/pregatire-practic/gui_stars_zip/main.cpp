#include <QApplication>
#include "Service.h"
#include "starsModels.h"
#include "gui_stars.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    std::ofstream fout("testing.txt");
    Repository repository("astronauts.txt", "stars.txt");
    auto* model = new starsModel(repository);
    fout << model << '\n';

    Service service(repository);
    for (const auto& astronaut : service.getAstronauts())
    {
        auto* astronautWindow = new AstronautWindow(astronaut, service, model);
        astronautWindow->show();
    }
    return QApplication::exec();
}