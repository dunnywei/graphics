#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <QtOpenGl\qglwidget>
#include "MEGWindow.h"

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

MeGlwindow::MeGlwindow(MeGlwindow *parent) :QGLWidget(parent)
{
	swapBuffers();

}

void sendDataToOpenGL()
{
    const float RED_TRIANGLE_Z=+0.5f;
    const float BLUE_TRIANGLE_Z=-0.5f;

	GLfloat verts[]=
	{
		/*
		Lec 10(01:29)->Shader is a program executed on the graphic card
		Currently, the foloinwg code is executed on the CPU
		->Shader goes to the graphic pipeline.
		->We need to customerize the piplelie
        ->(02:32) Shader's responsiblity is to shade the pixel
        ->(02:57) Vertex shader and fragment shader(pixel) (3:31) 
        ->(03:55) While hitting glDrawElements, Opengl will take its vertex into vertex shader in order
        -> Vertex shader has to output two things:positions on the screen and any other thing(custom data)(4:26)
        ->Once the OpenGl has the position (3 vertices) making one triangle
        ->(4:35) If the OpenGL wishes to draw the triangle, it has to fill every single pixes 
        //inside that triangle
        -> (4:55) Every single pixel(framgent), OpenGl has to execute fragment shader
        -> (5:13) For the vertex shader, it needs to run 5 times
        -> (5:22) for the fragment shader, it needs to run several times depending on 
        # of framents in the triangle
        ->(5:31) Postion data from OpenGl(GPU)
        ->(5:38) The custom data comes back in to the fragment shader
        ->(5:40) The GPU interpolate the data from vertex to vertex
        ->(5:51) The triangle (left is blue, down is red) so it will blend
        from blue to red eventually from top to buttom
        -> (6:18) We need to write the fragment shader which will run the CPU
        at the end
        -> (6:20) The only thing fragment shader has to output is R,G,B,A color
        -> (6:35) We know who much does each RGB color applies to each fragment
        in every single pixel
        -> (7:18) GPU is super powerful since they do in parallel. It means GPU is
        good to do the floating point arithmatic including vector math

       ->(7:48) GPU load several vertex(in our case verts[]) in parallel
        */
        /*
        */
        //Start of video 7
         -1.0f,-1.0f,RED_TRIANGLE_Z,//0
        +1.0f,+0.0f,+0.0f, //For 3 vertex's color in RGB lec 9  
        +0.0f,+1.0f,-1.0f,//1
        //+0.0f,+1.0f,RED_TRIANGLE_Z,//1
        +0.0f,+0.0f,+1.0f, //For 4 vertex's color in RGB lec 9
        //+1.0f,+0.0f,+0.0f, //For 4 vertex's color in RGB lec 9

        +1.0f,-1.0f,RED_TRIANGLE_Z,//2
        +1.0f,+0.0f,+0.0f, //For 4 vertex's color in RGB lec 9


        -1.0f, +1.0f,BLUE_TRIANGLE_Z, //3
        +1.0f,+0.0f,+1.0f, //For 0 vertex's color in RGB lec 9
        
        +0.0f,-1.0f,BLUE_TRIANGLE_Z,//4
        +1.0f,+0.0f,+1.0f, //For 3 vertex's color in RGB lec 9  
        
        +1.0f,+1.0f,BLUE_TRIANGLE_Z,//5
        +1.0f,+0.0f,+1.0f, //For 4 vertex's color in RGB lec 9

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
                          3, //Two floating points make one vetrices 
                          GL_FLOAT,
                          GL_FALSE,//normalized
                          sizeof(float)*6,//strides->distance. of the 0 vertex to 1 vertex 
                          0);//lecture 9(04:34),byte offset from the beginning of the buffer
                             //since verts[] starts at the beginning of the array (5:52)

	glEnableVertexAttribArray(1);//second attribute, color lecture 9(6:13)
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,(char*)(sizeof(float)*3);//->Lecture 9(6:44)


    Glushort indices[]= {0,1,2,3,4,5};
    //can use GLuint for 32 bits or GLubyte for 8bit, Glushort gives 16 bits
    GLuint indexBufferID;
    glGenBuffers(1,&indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    //Video 7 @8:25 important concept for bining GL_ELEMENT_ARRAY_BUFFER and Buufers
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW );

    //it is an integer and unsign
	//end of video 7
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
void MeGlwindow::paintGL()
{
	glclear(GL_DEPTH_BUFFER_BIT);
	QSize viewport_size = size();
	glViewport(0, 0, viewport_size.width(), viewport_size.height());

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//start of video 7
	//glDrawArrays(GL_TRIANGLES, 0, 6);//Every three vertices make triangle
	
	//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);

    //end of video 7


	
	
	
}

void MeGlwindow::resizeGL(int w, int h)
{
	QGLWidget::resize(w, h);
}