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

    cerr << "type = 0x" << hex << type
         << ", severity = 0x" << severity
         << ", message = " << message << endl;
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, 800.0 / 600.0, 1.0, 10.0);

    // Intentional invalid enum to trigger the debug callback
    glEnable(0xFFFFFFFF);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);

    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-0.6f, -0.6f, 0.0f);
        glVertex3f( 0.6f, -0.6f, 0.0f);
        glVertex3f( 0.6f,  0.6f, 0.0f);
        glVertex3f(-0.6f,  0.6f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q17");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
        glEnable(GL_DEPTH_TEST);
        init();
        glutMainLoop();
    }
    
#else
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    glEnable(GL_DEPTH_TEST);
    init();
    glutMainLoop();
#endif

    return 0;
}
