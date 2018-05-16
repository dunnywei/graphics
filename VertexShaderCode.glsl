#version 430

in layout(location=0) vec2 position;
in location(layout=1) vec3 vertexColor;

out vec3 theColor;
void main()
{
   gl_Position=vec4(position,0.0,1.0);
   theColor=vertexColor;
   
};