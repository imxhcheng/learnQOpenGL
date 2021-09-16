#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

class myGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:

	myGlWidget(QWidget *parent = nullptr);
protected:

	void paintGL();
	void initializeGL();
	void resizeEvent(QResizeEvent *e);

private:
	QOpenGLShaderProgram *program;
	QOpenGLVertexArrayObject vao;
	QOpenGLBuffer vbo;

	QOpenGLTexture		*m_texture;

};

#endif // MYGLWIDGET_H
