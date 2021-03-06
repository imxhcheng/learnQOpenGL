#ifndef NV12RENDER_H
#define NV12RENDER_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class Nv12Render : public QOpenGLFunctions
{
public:
	Nv12Render() = default;
	Nv12Render(const Nv12Render&) = delete;
	~Nv12Render();

	void initialize();
	void render(uchar* m_py, uchar* m_pu, int width, int height);
	void render(uchar *nv12Ptr, int w, int h);

private:
	QOpenGLShaderProgram program;
	GLuint idY, idUV;
	QOpenGLBuffer vbo;
};

#endif // NV12RENDER_H