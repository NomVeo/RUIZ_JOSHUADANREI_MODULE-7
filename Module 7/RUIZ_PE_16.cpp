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

void drawScene() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -4.0f);
    glRotatef(25.0f, 1.0f, 1.0f, 0.0f);

    glColor3f(0.2f, 0.7f, 0.4f);
    glutSolidTeapot(0.8);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // LEFT: Orthographic projection
    glViewport(0, 0, 400, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 1.0, 10.0);

    drawScene();

    // RIGHT: Perspective projection
    glViewport(400, 0, 400, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 400.0 / 600.0, 1.0, 10.0);

    drawScene();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q16");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK) {
        glEnable(GL_DEPTH_TEST);
        glutMainLoop();
    }
#else
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
#endif
    return 0;
}
