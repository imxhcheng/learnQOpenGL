#pragma once

#include <QOpenGLWidget>
#include "Nv12Render.h"

const int g_width = 3264;
const int g_height = 2448;

class myOPenglWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	myOPenglWidget(QWidget *parent);
	~myOPenglWidget();

	void initializeGL(); //调用上面渲染类的初始化函数
	void paintGL();//调用上面渲染类的渲染函数

	uchar* readYuv(char* path);

private:
	Nv12Render	m_Nv12Render;

	uchar*		m_pNv12Ptr;
};
