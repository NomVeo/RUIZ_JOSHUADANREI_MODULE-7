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

void drawScene() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.3f, 0.7f, 0.9f);
    glutSolidTeapot(0.8);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // LEFT VIEWPORT: Fixed camera
    glViewport(0, 0, 400, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 400.0 / 600.0, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        4.0, 2.0, 4.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glColor3f(0.3f, 0.7f, 0.9f);
    glutSolidTeapot(0.8);

    // RIGHT VIEWPORT: Animated orbiting camera
    glViewport(400, 0, 400, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 400.0 / 600.0, 1.0, 10.0);

    float eyeX = 4.0f * sinf(angle);
    float eyeZ = 4.0f * cosf(angle);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eyeX, 2.0f, eyeZ,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glColor3f(0.9f, 0.5f, 0.2f);
    glutSolidTeapot(0.8);

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
    glutCreateWindow("Ruiz_Q19");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK) {
        glEnable(GL_DEPTH_TEST);
        glutTimerFunc(50, animate, 0);
        glutMainLoop();
    }
    
#else
    glEnable(GL_DEPTH_TEST);
    glutTimerFunc(50, animate, 0);
    glutMainLoop();
#endif

    return 0;
}
