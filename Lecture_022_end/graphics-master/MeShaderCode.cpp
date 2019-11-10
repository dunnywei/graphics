const char* vertexShaderCode=
"#version 430\r\n"
"\n"
"in layout(location=0) vec2 position;\n"
"//in layout(location=1) vec3 vertexColor;\n"
"in location(layout=1) vec3 vertexColor;\n"
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
