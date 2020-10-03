The program takes input a .obj file and displays the 3D model.
The model can be controlled by the following mouse movements:
  1. Rotation: Hold the left mouse button and drag your mouse cursor in the
     direction you want it to rotate.
  2. Zoom In/Out: Hold the right mouse button and drag your mouse cursor
     upwards to zoom in and downwards to zoom out.

PACKAGES REQUIRED:
1. OpenGL (GL and GLU)
2. GLUT

STEPS TO RUN THE PROGRAM:
$ g++ main.cpp -lGL -lGLU -lglut
$ ./a.out

SPECIFICATIONS
1. The window size is set to 1280 x 720 pixels (so that appears to be 
   full-screen).
2. 'Esc' key press closes the window and quits the program.