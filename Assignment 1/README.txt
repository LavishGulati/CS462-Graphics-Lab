The program takes input a .obj file and displays the 3D model.
The model rotates around the y-axis to give a sense of 3D (else it will just
be a 2D projection of the 3D object).

PACKAGES REQUIRED:
1. OpenGL
2. GLUT

STEPS TO RUN THE PROGRAM:
$ g++ main.cpp -lGL -lGLU -lglut
$ ./a.out

SPECIFICATIONS
1. The window size is set to 1280x720 pixels (so that appears to be full-screen).
2. Rotation is set to 2 degrees per 25 ms around the y-axis.

BONUS FEATURES
1. Rotation of the 3D model around y-axis.
2. 'Esc' key press handled to close the window.
3. Resized the object so that it appears bigger than original.