#include "tree.h"

const GLfloat Tree::mat_trunk[] = { 0.4, 0.3, 0.04, 1 };
const GLfloat Tree::mat_leaves[] = { 0, 1, 0, 1 };

Tree::Tree()
{
  draw();
}

void Tree::draw() const
{
  drawTrunk();
  drawLeaves();
}

void Tree::drawTrunk() const
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_trunk);
  glColor3f(0.7f, 0.5f, 0.04f);
  glPushMatrix();
  glScalef(0.5, 2, 0.5);
  glutSolidCube(1);
  glPopMatrix();
}

void Tree::drawLeaves() const
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_leaves);
  glColor3f(0, 1, 0);
  glPushMatrix();
  glTranslatef(0, 1, 0);
  glRotatef(-90, 1, 0, 0);
  glutSolidCone(1.5, 4, 5, 3);
  glPopMatrix( );
}
