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

bool depthEnabled = true;

void drawTriangle(float z, float r, float g, float b) {
    glColor3f(r, g, b);

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.7f, -0.6f, z);
        glVertex3f( 0.7f, -0.6f, z);
        glVertex3f( 0.0f,  0.7f, z);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (depthEnabled) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -3.0f);

    // Draw NEAREST triangle FIRST
    drawTriangle(0.5f, 1.0f, 0.2f, 0.2f);  // Red (near)

    // Draw MIDDLE triangle SECOND
    drawTriangle(0.0f, 0.2f, 1.0f, 0.2f);  // Green (middle)

    // Draw FARTHEST triangle LAST
    drawTriangle(-0.5f, 0.2f, 0.2f, 1.0f); // Blue (far)

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (double)w / h, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'd' || key == 'D') {
        depthEnabled = !depthEnabled;

        if (depthEnabled) {
            cout << "Depth Test: ON" << endl;
        } else {
            cout << "Depth Test: OFF" << endl;
        }

        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q14");

#ifndef __APPLE__
    glewInit();
#endif

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
