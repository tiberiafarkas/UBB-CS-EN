//#include "question_site.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include "UserView.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repository repository{};
    Service service{ repository }; 
    
    for (auto& user : service.getUsers())
    {
		UserView* userView = new UserView{ user, service };  
		userView->show(); 
	}


    return a.exec();
}
