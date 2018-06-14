#version 430

in layout(location=0) vec3 position;
in location(layout=1) vec3 vertexColor;

out vec3 theColor;
void main()
{
   //gl_Position=vec4(position,0.0,1.0);
   gl_Position=vec4(position,1.0);

   //Lecture 20->specifiy the z value is always 0 (3:18)
   theColor=vertexColor;
   
};