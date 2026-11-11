#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
using namespace std;

void drawSquare() {
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f,  0.2f);
        glVertex2f(-0.2f,  0.2f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // Translate first, then scale
    glLoadIdentity();
    glTranslatef(-0.4f, 0.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.0f);
    glColor3f(0.9f, 0.3f, 0.2f);
    drawSquare();

    // Scale first, then translate
    glLoadIdentity();
    glScalef(1.5f, 1.5f, 1.0f);
    glTranslatef(0.4f, 0.0f, 0.0f);
    glColor3f(0.2f, 0.6f, 0.9f);
    drawSquare();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q08");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK)
        glutMainLoop();
#else
    glutMainLoop();
#endif
    return 0;
}
