#include "QOpenGL02.h"
#include "myGLWidget.h"
#include <QtWidgets/QApplication>
#include <omp.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	myGlWidget* pGlWidget = new myGlWidget;
	pGlWidget->show();
	 
	//int threads = omp_get_max_threads();

    return a.exec();
}
