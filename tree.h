#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include <GL/glut.h>

class Tree
{
  public:
    Tree();

  private:
    static const GLfloat mat_trunk[];
    static const GLfloat mat_leaves[];
    void draw() const;
    void drawTrunk() const;
    void drawLeaves() const;
};

#endif
