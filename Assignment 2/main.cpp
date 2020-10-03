// Libraries needed by the program
#include <iostream>
#include <vector>
#include <fstream>
#include <GL/glut.h>

using namespace std;

// Defining macros
#define pb push_back

// Defining a face of the model formed by three vertex indexes
struct face{
public:
    int v1, v2, v3;

    face(int x, int y, int z){
        v1 = x;
        v2 = y;
        v3 = z;
    }
};

// obj file name
string filename = "lowpolybunny.obj";
// Variables to store the obj data
char mode;
GLdouble x, y, z;
vector<GLdouble> vx, vy, vz;
vector<face> faces;
// Variables to store rotation angles and scale/size of the model
double sdepth = -30, sphi = 0, stheta = 0;
// Indicate the coordinates of mouse pointer
int downX, downY;
// Indicate whether left or right button of mouse was pressed
bool leftButton = false, rightButton = false;

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

void readModelObj(string filename){
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
            faces.pb(face(x-1, y-1, z-1));
		}
	}
}

void display(){
    // Clears the initial window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Handles the matrix operations related to translation and rotation
    glTranslated(0, 0, sdepth);
    glRotated(-stheta, 1, 0, 0);
    glRotated(sphi, 0, 1, 0);

    glPushMatrix();
    // Translates the object in x, y, z axis
    glTranslated(1, -3, 0);
    // Scales the object size
    glScaled(20, 20, 20);
    
    // Constructs the model with faces and vertices data
    // Each face is represented by three vertices (hence GL_TRIANGLES)
    glBegin(GL_TRIANGLES);
    glColor3d(1, 1, 1);
    for(int i = 0; i < faces.size(); i++){
        int v1 = faces[i].v1;
        int v2 = faces[i].v2;
        int v3 = faces[i].v3;

        glVertex3d(vx[v1], vy[v1], vz[v1]);
        glVertex3d(vx[v2], vy[v2], vz[v2]);
        glVertex3d(vx[v3], vy[v3], vz[v3]);
    }

    // Flush the matrix for display
    glEnd();
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}

// Handles the mouse callback for left and right buttons
void mouseCallback(int button, int state, int x, int y){
    downX = x; downY = y;
    leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
    rightButton = ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN));
    glutPostRedisplay();
}

// Handles the mouse motion callback
void motionCallback(int x, int y){
    // If left button pressed, update the rotation angles
    if(leftButton){
        sphi -= (x-downX)/4;
        stheta -= (downY-y)/4;
    }
    // If right button pressed, update the scale/size
    if(rightButton){
        sdepth += (downY-y)/10;
    }

    downX = x; downY = y;
    glutPostRedisplay();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    // GLUT_DOUBLE and GLUT_DEPTH are required for 3D object rotation
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    // Initial window position = (0, 0)
    glutInitWindowPosition(0, 0);
    // Window size = 1280 x 720 px
    glutInitWindowSize(1280, 720);

    // Title of window
    glutCreateWindow("Assignment 2");
    initRendering();
    readModelObj(filename);

    // Callback function 'display'
    glutDisplayFunc(display);
	
    // Callback functions for various events
    glutKeyboardFunc(handleKeyPress);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutReshapeFunc(handleResize);

    // Infinite loop so that the screen doesn't quit immediately
    glutMainLoop();
}