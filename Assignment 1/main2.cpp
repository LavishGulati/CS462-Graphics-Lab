// Libraries needed by the program
#include <iostream>
#include <vector>
#include <fstream>
#include <GL/glut.h>

using namespace std;

// Defining macros
#define pb push_back

// obj file name
string filename = "lowpolybunny.obj";
// Variables to store the obj data
char mode;
GLdouble x, y, z;
vector<GLdouble> vx, vy, vz;
// Variables to store rotation angles
double angle = 0.0;
double cameraangle = 30.0;

// Exits the window when 'Esc' key is pressed
void handleKeyPress(unsigned char key, int x, int y){
	switch(key){
		case 27:
			exit(0);
	}
}

// Initializes OpenGL for Depth rotation
void initRendering(){
    glEnable(GL_DEPTH_TEST);
}

// Handles rotation operations of object matrix
void handleResize(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, double(w)/double(h), 1, 200);
}

void display(){
    // Clears the initial window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(cameraangle, 0, 0, 0);
    glTranslated(0, 0, -10);

    glPushMatrix();
    // Translates the object in x, y, z axis
    glTranslated(0, -3, 0);
    // Scales the object size
    glScaled(15, 15, 15);
    // Rotates the object by the specified angle around y axis
    glRotated(angle, 0, 1, 0);

    // Stream to read the input file
    ifstream inFile;
	inFile.open(filename);
    // If file is not present, return
	if(!inFile){
		cout << "Unable to open file: " << filename << endl;
		return;
	}

	while(1){
        // If empty line found, break
		if(!(inFile >> mode)){
			break;
		}

		inFile >> x >> y >> z;
		// If mode is 'v', add the vertex to the vector
        if(mode == 'v'){
			vx.pb(x);
			vy.pb(y);
			vz.pb(z);
		}
        // If mode is 'f', draw the polygon with the specified vertices as
        // face of the object
		else if(mode == 'f'){
			glBegin(GL_POLYGON);
			glVertex3d(vx[x-1], vy[x-1], vz[x-1]);
			glVertex3d(vx[y-1], vy[y-1], vz[y-1]);
			glVertex3d(vx[z-1], vy[z-1], vz[z-1]);
			glEnd();
		}
	}

    glPopMatrix();
    glutSwapBuffers();
}

void update(int value){
    // Adds 2 degree to the angle
    angle += 2;
    if(angle > 360){
        angle -= 360;
    }

    glutPostRedisplay();
    // Recursive call after 25 ms to update the angle
    glutTimerFunc(25, update, 0);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    // GLUT_DOUBLE and GLUT_DEPTH are required for 3D object rotation
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    // Initial window position = (0, 0)
    glutInitWindowPosition(0, 0);
    // Window size = 1280x720 px
    glutInitWindowSize(1280, 720);

    // Title of window
    glutCreateWindow("Assignment 1");
    initRendering();

    // Callback function 'display'
    glutDisplayFunc(display);
	glutKeyboardFunc(handleKeyPress);
    glutReshapeFunc(handleResize);

    // Call 'update' function after 25 ms to update the angle
    glutTimerFunc(25, update, 0);

    // Infinite loop so that the screen doesn't quit immediately
    glutMainLoop();
}