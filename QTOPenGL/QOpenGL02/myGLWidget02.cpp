#include "myglwidget02.h"
#include <QtDebug>


//GLSL3.0版本后,废弃了attribute关键字（以及varying关键字），属性变量统一用in/out作为前置关键字
#define GL_VERSION  "#version 330 core\n"
#define GLCHA(x)  #@x           //加单引号,将x变为字符
#define GLSTR(x)  #x            //加双引号，将x变为字符串
#define GET_GLSTR(x) GL_VERSION#x


const char *vsrc = GET_GLSTR(

layout(location = 0) in vec3 aPos;		//位置变量的属性位置值为0
layout(location = 1) in vec3 aColor;	//颜色变量的属性位置值为1
out vec3 ourColor;		//向片段着色器输出一个颜色

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
}
);

const char *fsrc = GET_GLSTR(

out vec4 FragColor;
in vec3 ourColor;
void main(void)
{
	FragColor = vec4(ourColor, 1.0f);
}
);


myGlWidget::myGlWidget(QWidget *parent) :QOpenGLWidget(parent)
{

}


void myGlWidget::paintGL()
{
	// 绘制
   // glViewport(0, 0, width(), height());

	glClear(GL_COLOR_BUFFER_BIT);

	// 渲染Shader
	vao.bind();      //绑定激活vao
	glDrawArrays(GL_TRIANGLES, 0, 3);    //绘制3个定点,样式为三角形
	//glDrawArrays(GL_LINE_LOOP, 0, 3);    //绘制3个定点,样式为三条线

	vao.release();       //解绑

}
void myGlWidget::initializeGL()
{
	//0. 为当前环境初始化OpenGL函数
	initializeOpenGLFunctions();

	int nAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttributes);
	qDebug() << "Maximum of vertex attributes supported:" << nAttributes;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //设置背景色为白色


	//1.创建着色器程序
	program = new QOpenGLShaderProgram;
	program->addShaderFromSourceCode(QOpenGLShader::Vertex, vsrc);
	program->addShaderFromSourceCode(QOpenGLShader::Fragment, fsrc);
	program->link();
	program->bind();//激活Program对象


	//2.初始化VBO,将顶点数据存储到buffer中,等待VAO激活后才能释放
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,	1.0f,0.0f,0.0f,
	0.5f, -0.5f, 0.0f,	0.0f,1.0f,0.0f,
	0.0f, 0.5f, 0.0f,	0.0f,0.0f,1.0f,
	};

	vbo.create();
	vbo.bind();              //绑定到当前的OpenGL上下文,
	vbo.allocate(vertices, 18 * sizeof(GLfloat));
	vbo.setUsagePattern(QOpenGLBuffer::StreamDraw);  //设置为一次修改，多次使用

	//3.初始化VAO,设置顶点数据状态(顶点，法线，纹理坐标等)
	vao.create();
	vao.bind();

	program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(float));
	program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(float), 3, 6 * sizeof(float));

	program->enableAttributeArray(0);
	program->enableAttributeArray(1);

	//6.解绑所有对象
	vao.release();
	vbo.release();

}
void myGlWidget::resizeEvent(QResizeEvent *e)
{


}