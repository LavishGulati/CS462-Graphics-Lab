#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


void init(void)
{
   // GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   // GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   // glShadeModel (GL_SMOOTH);

   // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_position);
   // glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
   // GLfloat spot_direction[] = { 1.0, 1.0, 0.0, 1 };
    // glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display(){

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // glTranslatef(0, 0, 10);
  glutSolidSphere (1.0, 64, 32);
  // glTranslatef(0, 0, -10);
  glFlush ();

}

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
if (w <= h)
    glOrtho (-1.5, 1.5, -1.5*h/w, 1.5*h/w, -10.0, 10.0);
else
    glOrtho (-1.5*w/h, 1.5*w/h, -1.5, 1.5, -10.0, 10.0);
glMatrixMode (GL_MODELVIEW);
glLoadIdentity();
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
