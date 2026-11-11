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

void drawQuad() {
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
    glLoadIdentity();

    // Left quad
    glPushMatrix();
        glTranslatef(-0.6f, 0.0f, 0.0f);
        glColor3f(0.9f, 0.3f, 0.2f);
        drawQuad();
    glPopMatrix();

    // Middle quad: rotated 45 degrees
    glPushMatrix();
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glColor3f(0.2f, 0.7f, 0.9f);
        drawQuad();
    glPopMatrix();

    // Right quad
    glPushMatrix();
        glTranslatef(0.6f, 0.0f, 0.0f);
        glColor3f(0.3f, 0.8f, 0.3f);
        drawQuad();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q04");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK)
        glutMainLoop();
#else
    glutMainLoop();
#endif

    return 0;
}
