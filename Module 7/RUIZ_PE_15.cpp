#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
#include <cstdlib>
using namespace std;

#define BUFFER_OFFSET(i) ((void*)(i))

GLuint VBOid;
float angle = 0.0f;

// Four triangular sides and two triangles for the base
GLfloat vertices[] = {
    // Front
     0.0f,  0.8f,  0.0f,
    -0.6f, -0.5f,  0.6f,
     0.6f, -0.5f,  0.6f,

    // Right
     0.0f,  0.8f,  0.0f,
     0.6f, -0.5f,  0.6f,
     0.6f, -0.5f, -0.6f,

    // Back
     0.0f,  0.8f,  0.0f,
     0.6f, -0.5f, -0.6f,
    -0.6f, -0.5f, -0.6f,

    // Left
     0.0f,  0.8f,  0.0f,
    -0.6f, -0.5f, -0.6f,
    -0.6f, -0.5f,  0.6f,

    // Base triangle 1
    -0.6f, -0.5f,  0.6f,
     0.6f, -0.5f,  0.6f,
     0.6f, -0.5f, -0.6f,

    // Base triangle 2
    -0.6f, -0.5f,  0.6f,
     0.6f, -0.5f, -0.6f,
    -0.6f, -0.5f, -0.6f
};

GLfloat colors[] = {
    // Front
    1,0,0,  1,0,0,  1,0,0,
    // Right
    0,1,0,  0,1,0,  0,1,0,
    // Back
    0,0,1,  0,0,1,  0,0,1,
    // Left
    1,1,0,  1,1,0,  1,1,0,
    // Base
    0.5f,0.5f,0.5f,  0.5f,0.5f,0.5f,  0.5f,0.5f,0.5f,
    0.5f,0.5f,0.5f,  0.5f,0.5f,0.5f,  0.5f,0.5f,0.5f
};

void init() {
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices) + sizeof(colors),
        NULL,
        GL_STATIC_DRAW
    );

    glBufferSubData(
        GL_ARRAY_BUFFER, 0,
        sizeof(vertices), vertices
    );

    glBufferSubData(
        GL_ARRAY_BUFFER, sizeof(vertices),
        sizeof(colors), colors
    );

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
    glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(sizeof(vertices)));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 1.0, 10.0);

    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(angle, 1.0f, 0.0f, 0.0f);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBegin(GL_TRIANGLES);
        for (int i = 0; i < 18; i++) {
            glArrayElement(i);
        }
    glEnd();

    glutSwapBuffers();
}

void animate(int value) {
    angle += 1.0f;

    if (angle >= 360.0f)
        angle = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(50, animate, 0);
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBOid);
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q15");
    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

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
