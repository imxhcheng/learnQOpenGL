#include "QOpenGL03.h"
#include <QtWidgets/QApplication>
#include "myGLWidget03.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
	myGlWidget* p = new myGlWidget();
	p->show();
    return a.exec();
}
