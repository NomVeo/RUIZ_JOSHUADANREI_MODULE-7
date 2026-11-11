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

float baseAngle = 20.0f;
float jointAngle = 30.0f;

void drawSegment(float width, float length) {
    glBegin(GL_QUADS);
        glVertex2f(-width, 0.0f);
        glVertex2f( width, 0.0f);
        glVertex2f( width, length);
        glVertex2f(-width, length);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, -0.5f, 0.0f);

    // Base segment
    glPushMatrix();
        glRotatef(baseAngle, 0.0f, 0.0f, 1.0f);

        glColor3f(0.3f, 0.6f, 0.9f);
        drawSegment(0.1f, 0.5f);

        // Second joint inherits base rotation
        glPushMatrix();
            glTranslatef(0.0f, 0.5f, 0.0f);
            glRotatef(jointAngle, 0.0f, 0.0f, 1.0f);

            glColor3f(0.9f, 0.4f, 0.2f);
            drawSegment(0.08f, 0.4f);
        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a')
        baseAngle += 5.0f;
    else if (key == 'A')
        baseAngle -= 5.0f;
    else if (key == 's')
        jointAngle += 5.0f;
    else if (key == 'S')
        jointAngle -= 5.0f;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q18");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK)
        glutMainLoop();
#else
    glutMainLoop();
#endif

    return 0;
}
