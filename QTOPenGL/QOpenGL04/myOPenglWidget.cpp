#include "myOPenglWidget.h"

myOPenglWidget::myOPenglWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	m_pNv12Ptr = readYuv("D:\\A52sF_20210716058_2_3264x2448_3264x2448.NV12");
}

myOPenglWidget::~myOPenglWidget()
{
}

void myOPenglWidget::initializeGL()
{
	m_Nv12Render.initialize();
}

void myOPenglWidget::paintGL()
{
	m_Nv12Render.render(m_pNv12Ptr,g_width,g_height);
}

uchar* myOPenglWidget::readYuv(char* path)
{
	FILE *fp;
	unsigned char * buffer;
	long size = g_width * g_height * 3 / 2;

	if ((fp = fopen(path, "rb")) == NULL)
	{
		printf("cant open the file");
		exit(0);
	}

	buffer = new unsigned char[size];
	memset(buffer, '\0', size);
	fread(buffer, size, 1, fp);
	fclose(fp);
	return buffer;
}
