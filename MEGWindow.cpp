#include <GL\glew.h>
#include <QtOpenGl\qglwidget>
#include "MEGWindow.h"

MeGlwindow::MeGlwindow(MeGlwindow *parent) :QGLWidget(parent)
{
	swapBuffers();

}

void MeGlwindow::initalizaeGL()
{
	
	glewInit();

	GLfloat verts[]=
	{
		+0.0f, +100.0f,
		-100.0f,-100.0f,
		+100.0f,-100.0f,
	};
	GLuint mybufferID;
	glGenBuffers(1, &mybufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mybufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);//first attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	


}
void MeGlwindow::paintGL()
{
	QSize viewport_size = size();
	glViewport(0, 0, viewport_size.width(), viewport_size.height());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	
	//glClearColor(1, 0, 0, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	
	//glViewport(0, 0, width(), height());
	/*
	QSize viewport_size = size();
	glViewport(0, 0, viewport_size.width(), viewport_size.height());

	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 5, 7); // near and far match your triangle Z distance
	glMatrixMode(GL_MODELVIEW);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	*/
	/*
	QSize viewport_size = size();
	glViewport(0, 0, viewport_size.width(), viewport_size.height());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 5, 7); // near and far match your triangle Z distance

	glMatrixMode(GL_MODELVIEW);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
	
	setAutoBufferSwap(true);
	
	*/
	
}

void MeGlwindow::resizeGL(int w, int h)
{
	QGLWidget::resize(w, h);
}