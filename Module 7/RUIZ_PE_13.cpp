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

#define BUFFER_OFFSET(i) ((void*)(i))

GLuint VBOid;

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f
};

void init() {
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    // Reserve space for both position and color data
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
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBegin(GL_QUADS);
        for (int i = 0; i < 4; i++) {
            glArrayElement(i);
        }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q13");
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
