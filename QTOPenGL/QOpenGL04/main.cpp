#include "myOPenglWidget.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	myOPenglWidget *w = new myOPenglWidget(nullptr);
    w->show();

    return a.exec();
}
