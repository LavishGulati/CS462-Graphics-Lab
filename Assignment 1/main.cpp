#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>

using namespace std;

#define pb push_back

string filename = "lowpolybunny.obj";
char mode;
GLdouble x, y, z;
vector<GLdouble> vx, vy, vz;

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
    
	ifstream inFile;
	inFile.open(filename);
	if(!inFile){
		cout << "Unable to open file: " << filename << endl;
		return;
	}

	while(1){
		if(!(inFile >> mode)){
			break;
		}

		inFile >> x >> y >> z;
		if(mode == 'v'){
			vx.pb(x);
			vy.pb(y);
			vz.pb(z);
		}
		else if(mode == 'f'){
			glBegin(GL_POLYGON);
			glVertex3d(vx[x-1], vy[x-1], vz[x-1]);
			glVertex3d(vx[y-1], vy[y-1], vz[y-1]);
			glVertex3d(vx[z-1], vy[z-1], vz[z-1]);
			glEnd();
		}
	}
	
    glFlush();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Assignment 1");

    glutDisplayFunc(display);
    
	glutMainLoop();
}