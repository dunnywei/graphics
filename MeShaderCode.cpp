const char* vertexShaderCode=
"#version 430\r\n"
""
"in layout(location=0) vec2 position;"
"in layout(location=1) vec3 vertexColor;"
""
"out vec3 theColor;"
"void main()"
"{"
   "gl_position=vec4(position,0.0,1.0);"
   "theColor=vertexColor;"
   "//lec_13->3:41"
"}";

const char* fragmentShaderCode=
"#version 430\r\n"
""
"out vec4 daColor;"
"in vec3 theColor;"
"void main()"
"{"
   "//daColor=vec4(0.0,1.0,0.0,1.0);"
   "//lec_13->0:11->(RGBA)turn everything in to green"
   ""
   "daColor=vec4(theColor,1.0);"
"}";

//Lecture_14
//how many times does vertex shader execute? (00:36)
//Three times since there are only three vertexes (0:45)
//How many times does fragement shader execute? (00:53)
//There are a lot of fragments (pixels) required to draw (1:11)
//For now we assume fragments and pixels are the same
//how does hardware know what value to pass to the fragment shader(1:36)
//For the triangle, we have top bue,left buttom green and right buttom red (1:56)
//hardware will interpolate between two points. There is a video named lerp for linear interplation(2:03)
//blends=interpolate between the value (02:12) 
//When we send the data out of the vertex shader, the hardware do the interpolation(blend) (2:28)
//Should watch lerp video fro jamie king (3:49)
//