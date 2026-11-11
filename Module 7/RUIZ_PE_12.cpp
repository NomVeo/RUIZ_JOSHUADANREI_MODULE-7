#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

float angle = 0.0f;

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float eyeX = 4.0f * sinf(angle);
    float eyeZ = 4.0f * cosf(angle);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        eyeX, 1.0f, eyeZ,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );

    // Fixed quad: no glRotatef() is used
    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-0.7f, -0.7f, 0.0f);
        glVertex3f( 0.7f, -0.7f, 0.0f);
        glVertex3f( 0.7f,  0.7f, 0.0f);
        glVertex3f(-0.7f,  0.7f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

void animate(int value) {
    angle += 0.02f;

    if (angle >= 6.2831853f)
        angle = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(50, animate, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q12");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK) {
        init();
        glutTimerFunc(50, animate, 0);
        glutMainLoop();
    }
    
#else
    init();
    glutTimerFunc(50, animate, 0);
    glutMainLoop();
#endif

    return 0;
}
