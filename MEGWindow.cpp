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
		/*
		+0.0f, +100.0f, //First group vertices for making the 1st triangle
		-100.0f,-100.0f,
		+100.0f,-100.0f,

        +0.0f,+0.0f,//problem? too many redundency of +0.0f,+0.0f so the solution is indeces,index buffers or element array  
        -1.0f,-1.0f,
        +1.0f,-1.0f,
        */
        //Start of video 7
        +0.0f, +100.0f, //0
		-100.0f,-100.0f,//1
		+100.0f,-100.0f,  //2
        -1.0f,-1.0f,//3
        +1.0f,-1.0f,//4
        //So 0|1|2 makes 1st triangle and 0|3|4 make 2nd triangle
        //end of video 7
        

	};
	//The order of verts matter
	/*
	GLuint mybufferID;
	glGenBuffers(1, &mybufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mybufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);//first attribute
	glVertexAttribPointer(0, 
                          2, //Two floating points make one vetrices 
                          GL_FLOAT, GL_FALSE, 0, 0);
    */
	//start of video 7
    
    GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);//first attribute
	glVertexAttribPointer(0, 
                          2, //Two floating points make one vetrices 
                          GL_FLOAT, GL_FALSE, 0, 0);

    Glushort indices[]= {0,1,2,0,3,4};
    GLuint indexBufferID;
    glGenBuffers(1,&indexBufferID); //starts here at 6:20
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    //Video 7 @8:25 important concept for bining GL_ELEMENT_ARRAY_BUFFER and Buufers
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW );

    //it is an integer and unsign
	//end of video 7
	


}
void MeGlwindow::paintGL()
{
	QSize viewport_size = size();
	glViewport(0, 0, viewport_size.width(), viewport_size.height());

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//start of video 7
	//glDrawArrays(GL_TRIANGLES, 0, 6);//Every three vertices make triangle
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
    //end of video 7


	
	
	
}

void MeGlwindow::resizeGL(int w, int h)
{
	QGLWidget::resize(w, h);
}