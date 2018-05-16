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

/*Lecture_14
-how many times does vertex shader execute? (00:36)
-Three times since there are only three vertexes (0:45)
-How many times does fragement shader execute? (00:53)
-There are a lot of fragments (pixels) required to draw (1:11)
-For now we assume fragments and pixels are the same
-how does hardware know what value to pass to the fragment shader(1:36)
-For the triangle, we have top bue,left buttom green and right buttom red (1:56)
-hardware will interpolate between two points. There is a video named lerp for linear interplation(2:03)
-blends=interpolate between the value (02:12) 
-When we send the data out of the vertex shader, the hardware do the interpolation(blend) (2:28)
-Should watch lerp video fro jamie king (3:49)
*/

/*Lecture 15
-it is like using OO concept (01:26)
-GLuint vertexShaderID is like a handler. Treat them as pointer of an object (01:56)
-think them as OO programming (6:33)
|*/

/*Lecture 16
-when we use glCompileShader, we want to see the error message (1:16)
-Need to check if coppile works (1:26)
*/

/*Lecture 18
-raadShaderCode(""); (1:37)(1:49)

*/