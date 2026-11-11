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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);

    glColor3f(0.2f, 0.5f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-0.7f, -0.7f, 0.0f);
        glVertex3f( 0.7f, -0.7f, 0.0f);
        glVertex3f( 0.7f,  0.7f, 0.0f);
        glVertex3f(-0.7f,  0.7f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q02");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK) {
        init();
        glutMainLoop();
    }
#else
    init();
    glutMainLoop();
#endif

    return 0;
}
