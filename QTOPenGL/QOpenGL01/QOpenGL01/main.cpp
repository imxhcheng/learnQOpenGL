#include "QOpenGL01.h"
#include <QtWidgets/QApplication>
#include "myGLWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	myGlWidget* pGlWidget = new myGlWidget;
	pGlWidget->show();

    return a.exec();
}
