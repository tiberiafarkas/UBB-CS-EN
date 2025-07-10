//#include "screen_writing.h"
#include <QtWidgets/QApplication>
#include "repository.h"
#include "IdeaTabelModel.h"
#include "WriterView.h"
#include "tests.h"
#include <qdebug.h>

int main(int argc, char *argv[])
{
    testAll();
    qDebug() << "Tests passed";

    QApplication a(argc, argv);
    
    Repository repository;

    IdeaTabelModel* ideaTabelModel = new IdeaTabelModel{ repository };

    for (auto& w : repository.getWriters())
    {
        WriterView* writerView = new WriterView{w, repository, ideaTabelModel };
        writerView->show();
    }


    return a.exec();
}
