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

/*Lecture 19_OpenGL Fragment vs Pixel
-Fragment=potential pixel (0:23)
-fragment shader kicks out a RGBA value (0:37). This value may not be necessary shown up on the screen as a pixel(0:39)(0:41)
-Think fragment as a caterpillars and may potenally become a butterfy (0:51) if it succeeds (2:02)
-Output as a RGBA value but doesn't mean it is a pixel (1:08)
-draw red triangle then draw blue triangle. The red will overwrites blue when there is overlapping 
Painter algorithm(2:17)
-In order to have the red again. It required to draw red again (2:23)
-We need to make sure the red precedence over the blue triangle (3:12)
-Or red triangle is closer to the viewer than blue triangle (3:18)(3:24)
-(3:40)The precedence of red over blue is that when the OpenGL try to draw red but see the blue,
it will keep the red. Otherwise draw blue (4:16)
-When OpenGL try to fill the blue pixels from RGB value from fragment shader (5:16), I can't
draw you due to the red color has precedence over blue color (5:21)
-Some of fragments become pixels (5:41) but not all of the do
-the dpeth in OpenGL deals with the which color has the precedence (5:52)
*/

/*Lecture 20_OpenGL Depth Buffer
->x from left to right
->y from buttom to top
->z axis (0:53), coming straight out of the screen as -ve, (going in to the screen is +ve)->important (1:08)
->on Z axis the +1 is too far to see and -1 is too close to see(like clipping) (2:41)
->The vertex with greater Z value is further away from us or camer (3:27) with more depth (3:30)
->IF you are close to the camera or us you have less z value with less depth (3:37)
->If I give the red triangle with less depth so it will be closer to the camera or scene. It will 
be always on top of the blue triangle (3:56)
->we need to cover buffer(4:05)
->An image is a 2D array of pixels (4:08)
->No matter if it is a 2D or 3D image, it is a 2D dimension array of pixel (4:20)
->A pixel contains r,g,b values (4:24)
->two dimension array of triangle (4:57)
->We put the color including RGB into the buffer then dispalyed on the screen (6:03)
->We also have to worry about is the depth buffer (6:08)
->Dpeth buffer is also a 2D array (6:13) and storing one values (6:15). Dpeth of the
fragment (6:22)
->For example in both triangle, our case always make z=0 in vertex shader(6:28)(6:40)
->It makes every z=0 in this scene (6:44)
as 
gl_Position=vec4(position,0.0,1.0);
   //Lecture 20->specifiy the z value is always 0 (3:18)
->The z value has nothing to do with position (6:50) will be shown up on the screen (6:52)
->The only thing the OpenGL z value is used for (6:55) is the depth
->x and y (6:59) determine the where vertex will be displayed on the screen (7:02) z-value
determines the dpeth
->In default, the depth buffer is not turned on (7:10)(7:31)
->When we begin to render the scene, we want to make the farest depth (7:35)
->So we make our depth as +1 as the farest depth (8:06)
->When we try to render the scene, all of the RGB's color is 0 and we will try to clear out the buffer
as well (8:27)
->so we make 0,0,0 for RGB color (8:34)
->The z value for red triangle (8:44) to -0.5 so it is closer to the screen
->The z value for blue traingle (8:58) to +0.5 (9:02) so it is further to the screnn (9:05)
->we try to render both triangles(9:13)
->Red triangle will be rendered first (9:16)
->let's us pick the center. Now it is 000 in RGB befoe rendering red (9:26)
->Now it is 100 in RGB while rendering red(9:37).It is a fragment having a potential to
become pixel (9:41) 
->what's the depth of this fragment(9:46)? OpenGL looks at three vertices make the
triangle(9:49) then interpret the z depth(9:51) as three vertrices (9:54)
->since z value is for red triangle is 0.5 (10:02) so all the fragment inside the red triangle
has to be -0.5 as well (10:05)
-> hardware will do this so hardare takes the z value as -0.5 (10:12) and compare with the(10:21)
value stored in the depth buffer as 1.
-> since value -.5 is closer to the screen than the value 1 so it passed the test and become
pixel (10:40)
->so at the end. It will change the center from value of 000 to 100 with z=-0.5(10:58)(10:10)
->it will apply to all of the fragment with its assocaited depth (11:37)
->let's render the blue triangle (11:58)
->We need to set the color as 001 for RGB (12:21) with depth value 0.5
->We need to write the color buffer as 001 for RGB in color buffer (12:39)
->since the .5 > -0.5 so the fragment can't be dispalyed as pixel (12:54) since it fails
the depth test (13:09) 
*/

/*
 *Lecture_21->OpenGL glEnable Depth Test
->after enabling glEnable(GL_DEPTH_TEST);
->After we paint,we need to clear the buffer for the farest value(1:20) that we(OpenGL) are
interested in (1:23) by glclear(GL_DEPTH_BUFFER_BIT);
->we render the red triangle first (2:26)
->Buffer is a 2-D array (2:34)
->Let's examine one fragment and one pixel (2:42)
->Color buffer (BF) and Death buffer (DB) (2:51)
->clearDepthBUfer->DB is set to 1(2:56)
->Render out the triangle (3:0 *1)
->z postion for every vertex is 0 (3:22) from the statement of 
gl_position=vec4(position,0.0,1.0); in VertexShaderCode.glsl
->So in RGB will be 100 (3:36) for fragment. The depth buffer in Z position is 0 (3:50)
->so the hardware will check does z-value=0 less than 1 (3:59) since the answer is YES (4:13)
-> Therefore, the z-value will be updated as 0 (4:15) and the RGB value with 100 will 
become the pixel(4:22) into the color buffer (4:29)
->Then we render the blue triangle (4:47)
->The blue fragment is 001 in RGB (4:52)
->the depth is at 0.0 as well as (5:11) 
l_position=vec4(position,0.0,1.0);
->change the z value of vertex (6:10)
->change in GLfloat verts[] (6:56)
->change to glVertexAttribPointer for both glEnableVertexAttribArray(0); and glEnableVertexAttribArray(1);
->(7:38)
->change "in layout(location=0) vec2 position;" to "in layout(location=0) vec3 position;" in
VertexShader.glsl
->change "gl_Position=vec4(position,1.0);"

*/

/*
 *Lecture_22->OpenGL Depth Interpolation
 ->Range -1(Closer) to 1(further) for z value (0:24)
 ->change to     (0:37)
 glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_SHORT,0);
 ->what will happen if we set the  (1:06)
 RED_TRIANGLE_Z=1.0f
->what we are going to see is that black screen since when we clear the depth buffer, we clear all
the values to 1 (1:22).
->every vertex fails the depth test (1:28)since All the RED_TRIANGLE_Z is 1(1:30)
->If we set the RED_TRIANGLE_Z=-1.01 (2:40),red triangle is gone  (2:43)
->The reason is that it is behind the camera (2:53) so OPENGL won't render (2:53)
->Let's change to and RED_TRIANGLE_Z=+0.5f;     const float BLUE_TRIANGLE_Z=-0.5f;
and glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0); (3:07) so blue is on top of the red (3:13)
->change +0.0f,+1.0f,RED_TRIANGLE_Z to +0.0f,+1.0f,-1.0f->what will happen (3:53)(3:57)
->My guess is the interpolation occurs between the buttom red, middle blue, top red. There will be
another interpolation occurs between midddle blue and top red
->all blue triangle is at -0.5 in Z depth (5:05)
->all red triangles are at z=0.5 except the top at z=-1.0 (5:05)
->The top one is close to the camera (5:11)
->When we move down from th top, z value becomes larger and larger (5:16) or think as it gets
further into the scene (5:21)
->All the sudden at the sweet spot (9:39), Z_value_blue fragment < Z_value_red fragment (5:30)
->what happen if I change the color of vertex at top to blue (6:42) 
->we will see the blending of the color or interpolation between the top and sweet spot. Between them
,there are still a lot of blue(7:23), more blue than red (7:28). Unitl we hit the sweet spot, red start
to win (7:43). See the left half of the red triangle (7:43)
->vertex shader to fragment shader, hadware do some interpolation (7:56)
->We see the interpolation of the color again (8:05)
->we can also see the interpolation of the z value (8:11)
->(??)The z value of the red triangle is closer to the viewer at the top
as (+0.0f,+1.0f,-1.0f) but they give further and further away since Z value becomes larger as we move down 
due to +1.0f,-1.0f,RED_TRIANGLE_Z as RED_TRIANGLE_Z=+0.5f at buttom right
(8:17)
->as we can see, the z-depth buffer correlates with the color change from blue to red(8:21)
->Righ here where we cross the sweet spot (8:39)
->Therefore, we will see more red (8:40)
-1/3 of triangle since for the red triangle I have top one is blue and 
buttom left and buttom right are red (9:03)
-(comments from other)
-at 8:30, you were explaining about why the sweet spot is not at the center. 
I think is it because the bottom two red vertices depth is +0.5. 
Changing the depth to +0.0,   you will get the desired result.

*/

/*
 *Lecture_23->OpenGL Sending Triangles in Parts Using glBufferSubData
 ->Color buffer is two dimension array (00:11) of pixels for RGB and alpha(ignore for now)
 ->GPU is used To filling these color buffers
 ->writie some codes and witness some behavior (00:53)
 ->Every new frame, add new triangle on the screen (2:07
 ->deleting code (2:07) to (2:56)
 ->When we generte a buffer object (2:54), it only tells the property about the buffer.
 It doesnèt store the data (3:01)
 ->The data is store in the buffer of an array of bytes (3:06) in GPU and maintained by OpenGL
 (3:10)
 ->The buffer objects keep track of the buffer (3:14)
 ->If we want to add multi triangle for multi frames , we need to take different approach
 on our buffer objects (3:30)
 ->change the code to
 glBufferData(GL_ARRAY_BUFFER, 10000, NULL, GL_STATIC_DRAW);
(3:40)(4:04)
->OpenGL sees that we are passing pointer to the NULL data (4:04)
->So you don't have any data for me to copy (4:07), I will still allocate 1000 bytes (4:10)
-It is up to the progrmmer to fill the byte (4:13)
->everytime when I paint, I want to add a triangle (4:21)(4:27)
->Under PaintGL(), we will modify it so it will add a triangle everytime (4:42)
->add function of "sendAnotherTriToOpenGL()" (5:03)
->Declare "const float X_DELTA=0.1;" (7:24)
->everytime when we draw a new triangle, we will move to the right one (7:30)
->declare "uint numTris=0;" (7:43)
->we will have 3 vertices and 6 attributes per vertices (8:38)
->modify "sendAnotherTriToOpenGL()" (8:10)
->add "     const GL_FLOAT THIS_TRI_X=-1+numTris*X_DELTA;  " (10:21)
->
