#include "sem7.h"
#include <QtWidgets/QApplication>
#include "chatsession.h"
#include "chatwindow.h"
#include "user.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	ChatSession* chatSession = new ChatSession();

	User maia("maia15", "Maia");
	User john("john_doe", "John Doe");

	ChatWindow* chatWindow1 = new ChatWindow(maia, *chatSession);
	chatWindow1->setWindowTitle("Maia");

	ChatWindow* chatWindow2 = new ChatWindow(john, *chatSession);
	chatWindow2->setWindowTitle("John");
	chatWindow2->move(800, 150); // Move the second window to avoid overlap

    //sem7 window;
    chatWindow1->show();
	chatWindow2->show();
    return app.exec();
}
