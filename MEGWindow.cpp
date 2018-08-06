#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <QtOpenGl\qglwidget>
#include "MEGWindow.h"

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

const float X_DELTA=0.1;
uint numTris=0;
MeGlwindow::MeGlwindow(MeGlwindow *parent) :QGLWidget(parent)
{
	swapBuffers();

}

void sendDataToOpenGL()
{
    const float RED_TRIANGLE_Z=+0.5f;
    const float BLUE_TRIANGLE_Z=-0.5f;


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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, 10000, NULL, GL_STATIC_DRAW);

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
                          3, //Two floating points make one vetrices 
                          GL_FLOAT,
                          GL_FALSE,//normalized
                          sizeof(float)*6,//strides->distance. of the 0 vertex to 1 vertex 
                          0);//lecture 9(04:34),byte offset from the beginning of the buffer
                             //since verts[] starts at the beginning of the array (5:52)

	glEnableVertexAttribArray(1);//second attribute, color lecture 9(6:13)
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,(char*)(sizeof(float)*3);//->Lecture 9(6:44)


    
}

bool checkStatus(GLunit objectID,
	             PFNGLGETSHADERIVPROC objectProperyGetterFunc,
	             PFNGLGETSHADERINFOLOGPROC getInfoLogFunc
	             GLenum statusType)
{
	//start of letcture 17->3:58
	//PFNGLGETSHADERIVPROC(Lecture 17->5:13)
	//functio pointer->http://www-ee.eng.hawaii.edu/~tep/EE160/Book/chap14/section2.1.3.html
	//Lecture 17->6:15->6:44
    GLuint status;
    objectProperyGetterFunc(objectID,statusType,&status);
    //it means that the last argument could be the index vector as status[10];(4:15)
    //when we talk about array in OpenGL->it means list of sequence of int (4:21)
    if(status!=GL_TRUE)//4:51
    {
    	GLint infologLength;
        objectProperyGetterFunc(objectID,GL_INFO_LOG_LENGTH,&infologLength); //lecture 16->6:25
        GLchar *buffer=new GLchar[infologLength];

        GLsizei buffersize;
        getInfoLogFunc(objectID,infologLength,&buffersize,buffer);//Lecture 16->8:51
        std::cout<<"buffer is"<<buffer<<endl;//Lecture 16->9:48

        delete [] buffer;
        return false;
    }
    return true;
}

bool checkShaderStatus(GLuint shaderID)
{
    //start of lecture 16
    GLuint compileStatus;
    glGetShaderiv(shaderID,GL_COMPILE_STATUS,&compileStatus);
    //it means that the last argument could be the index vector as compileStatus[10];(4:15)
    //when we talk about array in OpenGL->it means list of sequence of int (4:21)
    if(compileStatus!=GL_TRUE)//4:51
    {
    	GLint infologLength;
        glGetshaderiv(shaderID,GL_INFO_LOG_LENGTH,&infologLength); //lecture 16->6:25
        GLchar *buffer=new GLchar[infologLength];

        GLsizei buffersize;
        glGetShaderInfoLog(shaderID,infologLength,&buffersize,buffer);//Lecture 16->8:51
        std::cout<<"buffer is"<<buffer<<endl;//Lecture 16->9:48

        delete [] buffer;
        return false;
    }
    return true;
    //end of lecture 16

   //return checkStatus(shaderID,glGetshaderiv,glGetShaderInfoLog,GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
    //start of lecture 17
    GLuint linkStatus;
    glGetProgramiv(programID,GL_LINK_STATUS,&linkStatus);

    //it means that the last argument could be the index vector as linkStatus[10];(4:15)
    //when we talk about array in OpenGL->it means list of sequence of int (4:21)
    if(linkStatus!=GL_TRUE)//4:51
    {
    	GLint infologLength;
        glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&infologLength); //lecture 16->6:25
        GLchar *buffer=new GLchar[infologLength];

        GLsizei buffersize;
        glGetProgramInfoLog(programID,infologLength,&buffersize,buffer);//Lecture 16->8:51
        std::cout<<"buffer is"<<buffer<<endl;//Lecture 16->9:48

        delete [] buffer;
        return false;
    }
    return true;
    //end of lecture 17
    //return checkStatus(shaderID,glGetProgramiv,glGetProgramInfoLog,GL_LINK_STATUS);

}

std::string readShaderCode(const char* fileName)
{
   ifstream meInput(fileName);
   if(!meInput.good())
   {
   	 std::cout<<"load file fail"<<fileName<<std::endl; //Lecture 16->03:21
   	 exit(1);
   }
   
   return std::string(
      std::istreambuf_iterator<char>(meInput),
      std::istreambuf_iterator<char>());//Lecture 16->06:53
}


void installShader()
{
   //lec12
   /*
   take the string from MeShaderCode.cpp and compile them
   */
	GLuint vertexShaderID=glCreateShader("GL_VERTEX_SHADER");
	GLuint fragmentShaderID=glCreateShader("GL_FRAGMENT_SHADER");
    const GLchar* adapter[1];
    //adapter[0]=vertexShaderCode;
    std::string temp=readShaderCode("VertexShaderCode.glsl");
    adapter[0]=temp.c_str();//Lecture 16->05:00->starts here


	glShaderSource(vertexShaderID,1,adapter,0);

    temp=readShaderCode("FragmentShaderCode.glsl");
    adapter[0]=temp.c_str();

	//adapter[0]=fragmentShaderID;

	glShaderSource(fragmentShaderID,1,adapter,0);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);
    
    if(!checkShaderStatus(vertexShaderID)||!checkShaderStatus(fragmentShaderID))
    {
    	return;
    }

    GLuint programID=glCreateProgram();
    //Lecture 17:Comment the following two causes linking error (0:14)
    //glAttachShader(programID,vertexShaderID);
    //glAttachShader(programID,fragmentShaderID);

    //end of lecture 16
    gllinkProgram(programID);

    if(!checkProgramStatus(programID)) //Lecture 17->2:07
    {
        return;
    }

    glUseProgram(programID);
}



void MeGlwindow::initalizaeGL()
{
	
	glewInit();
	glEnable(GL_DEPTH_TEST);
    sendDataToOpenGL();
	installShader();


}

void sendAnotherTriToOpenGL()
{
   //Lecture 23->(8:10)
   const GL_FLOAT THIS_TRI_X=-1+numTris*X_DELTA; 
   GL_FLOAT thisTri[]=
   {
      THIS_TRI_X,1.0f,0.0f,//position
      1.0f,0.0f,0.0f,//color

      THIS_TRI_X+X_DELTA,1.0f,0.0f,
      1.0f,0.0f,0.0f,

      THIS_TRI_X,0.0f,0.0f,
      1.0f,0.0f,0.0f,
   };

   glBufferSubData(GL_ARRAY_BUFFER,)
}
void MeGlwindow::paintGL()
{
	glclear(GL_DEPTH_BUFFER_BIT);
	QSize viewport_size = size();
	glViewport(0, 0, viewport_size.width(), viewport_size.height());

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//start of video 7
	//glDrawArrays(GL_TRIANGLES, 0, 6);//Every three vertices make triangle
	
	//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
	sendAnotherTriToOpenGL();
	glDrawArrays()

    //end of video 7


	
	
	
}

void MeGlwindow::resizeGL(int w, int h)
{
	QGLWidget::resize(w, h);
}