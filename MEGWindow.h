#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#endif ME_GL_WINDOW
#include <QtOpenGl\qglwidget>

class MeGlwindow:public QGLWidget
{
protected:
   void paintGL();
   void initalizaeGL();
   void resizeGL(int width, int height);

   
public:
	MeGlwindow(MeGlwindow *parent=0);
	
};