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

float angle = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, -0.3f);
        glVertex2f( 0.3f, -0.3f);
        glVertex2f( 0.3f,  0.3f);
        glVertex2f(-0.3f,  0.3f);
    glEnd();

    glutSwapBuffers();
}

void animate(int value) {
    angle += 2.0f;

    if (angle >= 360.0f)
        angle = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(50, animate, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q07");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK) {
        glutTimerFunc(50, animate, 0);
        glutMainLoop();
    }
#else
    glutTimerFunc(50, animate, 0);
    glutMainLoop();
#endif

    return 0;
}
