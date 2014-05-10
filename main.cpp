#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "tree.h"

GLsizei winWidth = 800, winHeight = 600;   

// materials
GLfloat mat_ground[] = { 0, 0.5, 0, 1.0 };

// camera angle of rotation
float angle = 0;

// camera direction vector
float lx = 0, lz = -1;

// camera position
float x = 0, z = 1;

// key states
float deltaAngle = 0, deltaMove = 0;
int xOrigin = -1;

void calcPosition(float deltaMove)
{
  x += deltaMove * lx * 0.1f;
  z += deltaMove * lz * 0.1f;
}

// Initialize method
void init()
{
  // Get and display your OpenGL version
  std::cout << "Your OpenGL version is " << glGetString(GL_VERSION) << std::endl;

  // Sky
  glClearColor(0, 1, 1, 0);

  GLfloat light_position[] = { 5, 5, 5, 0.0 };

  glShadeModel (GL_SMOOTH);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glLoadIdentity();
}

// Draw method
void displayFcn()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  gluLookAt(x, 1.25f, z,
      x + lx, 1,  z + lz,
      0, 1,  0);

  // Draw ground
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ground);
  glColor3f(0, 0.5f, 0);
  glBegin(GL_QUADS);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();

  // Draw trees
  for(int i = -3; i < 3; i++)
    for(int j = -3; j < 3; j++) {
      if (i == 0 && j == 0) {
        continue;
      }
      glPushMatrix();
      glTranslatef(i * 10.0, 0, j * 10.0);
      Tree tree;
      glPopMatrix();
    }

  glutSwapBuffers();
}

// Window redraw method
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
  float ratio = newWidth * 1.0 / newHeight;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, newWidth, newHeight);
  gluPerspective(45, ratio, 0.1f, 100);
  glMatrixMode(GL_MODELVIEW);

  winWidth = newWidth;
  winHeight = newHeight;

  return;
}

void animate(void)
{
  if (deltaMove) {
    calcPosition(deltaMove);
  }

  glutPostRedisplay();
}

void pressNormalKey(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;
    case 119:
      deltaMove = 0.5f;
      break;
    case 115:
      deltaMove = -0.5f;
      break;
  }
}

void releaseNormalKey(unsigned char key, int x, int y) 
{
  switch (key) {
    case 119:
    case 115:
      deltaMove = 0;
      break;
  }
}

void pressSpecialKey(int key, int x, int y)
{
  switch (key) {
    case GLUT_KEY_UP:
      deltaMove = 0.5f;
      break;
    case GLUT_KEY_DOWN:
      deltaMove = -0.5f;
      break;
  }
}

void releaseSpecialKey(int key, int x, int y) 
{
  switch (key) {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
      deltaMove = 0; 
      break;
  }
}

void mouseButton(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_UP) {
      angle += deltaAngle;
      xOrigin = -1;
    } else {
      xOrigin = x;
    }
  }
}

void mouseMove(int x, int y) {  
  if (xOrigin >= 0) {
    deltaAngle = (x - xOrigin) * 0.01f;
    lx = sin(angle + deltaAngle);
    lz = -cos(angle + deltaAngle);
  }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("FPS Test");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);

    // Input
    glutKeyboardFunc(pressNormalKey);
    glutKeyboardUpFunc(releaseNormalKey);
    glutSpecialFunc(pressSpecialKey);
    glutSpecialUpFunc(releaseSpecialKey);
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseButton);
    
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
