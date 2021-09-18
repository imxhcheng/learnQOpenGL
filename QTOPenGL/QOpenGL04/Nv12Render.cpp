#include "Nv12Render.h"
#include <QOpenGLTexture>
#include <QDebug>

Nv12Render::~Nv12Render()
{

}

void Nv12Render::initialize()
{
	initializeOpenGLFunctions();
	const char *vsrc =
		"attribute vec4 vertexIn; \
             attribute vec4 textureIn; \
             varying vec4 textureOut;  \
             void main(void)           \
             {                         \
                 gl_Position = vertexIn; \
                 textureOut = textureIn; \
             }";

	const char *fsrc =
		"varying mediump vec4 textureOut;\n"
		"uniform sampler2D textureY;\n"
		"uniform sampler2D textureUV;\n"
		"void main(void)\n"
		"{\n"
		"vec3 yuv; \n"
		"vec3 rgb; \n"
		"yuv.x = texture2D(textureY, textureOut.st).r; \n"
		"yuv.y = texture2D(textureUV, textureOut.st).r-0.5 ; \n"
		"yuv.z = texture2D(textureUV, textureOut.st).g-0.5 ; \n"
		/*"rgb = mat3( 1,       1,         1, \n"
		"0,       -0.39465,  2.03211, \n"
		"1.13983, -0.58060,  0) * yuv; \n"*/
		"rgb = mat3( 1,       1,         1, \n"
		"0,       -0.3455,	1.779, \n"
		"1.4075, -0.7169,  0) * yuv; \n"
		"gl_FragColor = vec4(rgb, 1); \n"
		"}\n";
	program.addShaderFromSourceCode(QOpenGLShader::Vertex, vsrc);
	program.addShaderFromSourceCode(QOpenGLShader::Fragment, fsrc);
	program.link();

	GLfloat points[]{
		-1.0f, 1.0f,
		 1.0f, 1.0f,
		 1.0f, -1.0f,
		-1.0f, -1.0f,

		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		0.0f,1.0f
	};
	vbo.create();
	vbo.bind();
	vbo.allocate(points, sizeof(points));

	GLuint ids[2];
	glGenTextures(2, ids);
	idY = ids[0];
	idUV = ids[1];
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Nv12Render::render(uchar* py, uchar* puv, int w, int h)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	program.bind();
	vbo.bind();
	program.enableAttributeArray("vertexIn");
	program.enableAttributeArray("textureIn");
	program.setAttributeBuffer("vertexIn", GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));
	program.setAttributeBuffer("textureIn", GL_FLOAT, 2 * 4 * sizeof(GLfloat), 2, 2 * sizeof(GLfloat));

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, idY);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, py);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, idUV);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, w >> 1, h >> 1, 0, GL_RG, GL_UNSIGNED_BYTE, puv);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	program.setUniformValue("textureUV", 0);
	program.setUniformValue("textureY", 1);
	glDrawArrays(GL_QUADS, 0, 4);
	program.disableAttributeArray("vertexIn");
	program.disableAttributeArray("textureIn");
	program.release();
}


void Nv12Render::render(uchar *nv12Ptr, int w, int h)
{
	if (!nv12Ptr)return;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	program.bind();
	vbo.bind();
	program.enableAttributeArray("vertexIn");
	program.enableAttributeArray("textureIn");
	program.setAttributeBuffer("vertexIn", GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));
	program.setAttributeBuffer("textureIn", GL_FLOAT, 2 * 4 * sizeof(GLfloat), 2, 2 * sizeof(GLfloat));

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, idY);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, nv12Ptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, idUV);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, w >> 1, h >> 1, 0, GL_RG, GL_UNSIGNED_BYTE, nv12Ptr + w * h);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	program.setUniformValue("textureUV", 0);
	program.setUniformValue("textureY", 1);
	glDrawArrays(GL_QUADS, 0, 4);
	program.disableAttributeArray("vertexIn");
	program.disableAttributeArray("textureIn");
	program.release();
}