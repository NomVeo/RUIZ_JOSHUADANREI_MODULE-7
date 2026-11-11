
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
#include <cstdlib>
using namespace std;

#define BUFFER_OFFSET(i) ((void*)(i))

GLuint VBOid;

float armAngle = 0.0f;

// Base quad position data
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.0f, 0.0f,
    -0.5f,  0.0f, 0.0f
};

// Base quad color data
GLfloat colors[] = {
    0.2f, 0.4f, 0.9f,
    0.2f, 0.4f, 0.9f,
    0.2f, 0.4f, 0.9f,
    0.2f, 0.4f, 0.9f
};

void GLAPIENTRY MessageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
) {
    cerr << "GL CALLBACK: ";

    if (type == GL_DEBUG_TYPE_ERROR)
        cerr << "** GL ERROR ** ";

    cerr << "message = " << message << endl;
}

void init() {
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    // Reserve space for positions and colors
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

    // Upload color data
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

    gluLookAt(
        0.0, 1.0, 4.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    // Draw the fixed color VBO base
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
    glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(sizeof(vertices)));

    glBegin(GL_QUADS);
        for (int i = 0; i < 4; i++) {
            glArrayElement(i);
        }
    glEnd();

    // Disable client states before immediate-mode arm
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    // Draw hierarchical arm above the base
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(armAngle, 0.0f, 0.0f, 1.0f);

        glColor3f(0.9f, 0.4f, 0.2f);
        glBegin(GL_QUADS);
            glVertex3f(-0.12f, 0.0f, 0.0f);
            glVertex3f( 0.12f, 0.0f, 0.0f);
            glVertex3f( 0.12f, 0.7f, 0.0f);
            glVertex3f(-0.12f, 0.7f, 0.0f);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void animate(int value) {
    armAngle += 2.0f;

    if (armAngle >= 360.0f)
        armAngle = 0.0f;

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
    glutCreateWindow("Ruiz_Q20");

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);

        init();
        glutTimerFunc(50, animate, 0);
        glutMainLoop();
    }

#else
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    init();
    glutTimerFunc(50, animate, 0);
    glutMainLoop();
#endif

    return 0;
}
