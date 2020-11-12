#include <GL/glut.h>

GLuint tex;
GLUquadric* sphere;

void make_tex(void)
{
    unsigned char data[256][256][3];
    for (int y = 0; y < 255; y++) {
    	for (int x = 0; x < 255; x++) {
    	    unsigned char *p = data[y][x];
    	    p[0] = p[1] = p[2] = (x ^ y) & 8 ? 255 : 0;
    	}
    }
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void init() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);

   glClearColor (0.5, 0.5, 1.0, 1.0);
   glShadeModel (GL_SMOOTH);

GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 0, 1, -2.5, 1 };
  GLfloat spot_direction[] = {0, -1, 0};

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
   glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);

  glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);

   glEnable(GL_DEPTH_TEST);

   make_tex();
    sphere = gluNewQuadric();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0, 0, -4);
    glBegin(GL_QUADS);

    glColor3f(0.48, 0.48, 0.48);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);

    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,3);
    glVertex3f(-1,1,3);

    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,2);
    glVertex3f(1,-1,2);
    glVertex3f(1,-1, -1);

    glColor3f(1, 1, 1);
    glVertex3f(-0.4,1,0.25);
    glVertex3f(0.4,1,0.25);
    glVertex3f(0.4,1,0.75);
    glVertex3f(-0.4,1,0.75);


    glColor3f(0, 0, 1);
    glVertex3f(1,1,3);
    glVertex3f(1,-1,3);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);

    glColor3f(1,0,0);
    glVertex3f(-1,1,3);
    glVertex3f(-1,-1,3);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glEnd();

    glColor3f(0.0625, 0.476, 0.0625);

//     GLfloat mat_amb_diff[] = { 0.1, 0.5, 0.8, 1.0 };
// glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,
//             mat_amb_diff);
    // GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    // GLfloat low_shininess[] = { 128 };
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
    glTranslatef(0.5, -0.5, 1);
    glutSolidSphere(0.25, 128, 64);
    glTranslatef(-0.5, 0.5, -1);

    glEnable(GL_TEXTURE_2D);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    glTranslatef(-0.5, -0.5, 1);
    gluSphere(sphere, 0.25, 128, 64);
    glTranslatef(0.5, 0.5, -1);

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0){
        height = 1;
    }

    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Assignment 3");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}
