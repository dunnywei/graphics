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
        +0.0f, +0.0f, //0
        +1.0f,+0,0f,+0.0f, //For 0 vertex's color in RGB lec 9
		+1.0f,+1.0f,//1
		+1.0f,+0.0f,+0.0f, //For 1 vertex's color in RGB lec 9
		-1.0f,+1.0f,  //2
		+1.0f,+0.0f,+0.0f, //For 2 vertex's color in RGB lec 9
        -1.0f,-1.0f,//3
        +1.0f,+0.0f,+0.0f, //For 3 vertex's color in RGB lec 9  
        +1.0f,-1.0f,//4
        +1.0f,+0.0f,+0.0f, //For 4 vertex's color in RGB lec 9

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

	glEnableVertexAttribArray(0);//first attribute, position
	/*
	glVertexAttribPointer(0, 
                          2, //Two floating points make one vetrices 
                          GL_FLOAT,
                          GL_FALSE,
                          0,//strides->distance. of the 0 vertex to 1 vertex 
                          0);
    */
    glVertexAttribPointer(0, 
                          2, //Two floating points make one vetrices 
                          GL_FLOAT,
                          GL_FALSE,//normalized
                          sizeof(float)*5,//strides->distance. of the 0 vertex to 1 vertex 
                          0);//lecture 9(04:34),byte offset from the beginning of the buffer
                             //since verts[] starts at the beginning of the array (5:52)

	glEnableVertexAttribArray(1);//second attribute, color lecture 9(6:13)
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,(char*)(sizeof(float)*2);//->Lecture 9(6:44)


    Glushort indices[]= {0,1,2,0,3,4};
    //can use GLuint for 32 bits or GLubyte for 8bit, Glushort gives 16 bits
    GLuint indexBufferID;
    glGenBuffers(1,&indexBufferID);
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