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
float middleAngle = 35.0f;
float tipAngle = 25.0f;

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

    glTranslatef(0.0f, -0.7f, 0.0f);

    // Base segment
    glPushMatrix();
        glRotatef(baseAngle, 0.0f, 0.0f, 1.0f);
        glColor3f(0.2f, 0.5f, 0.9f);
        drawSegment(0.08f, 0.45f);

        // Middle segment
        glPushMatrix();
            glTranslatef(0.0f, 0.45f, 0.0f);
            glRotatef(middleAngle, 0.0f, 0.0f, 1.0f);
            glColor3f(0.9f, 0.5f, 0.2f);
            drawSegment(0.07f, 0.35f);

            // Tip segment
            glPushMatrix();
                glTranslatef(0.0f, 0.35f, 0.0f);
                glRotatef(tipAngle, 0.0f, 0.0f, 1.0f);
                glColor3f(0.3f, 0.8f, 0.3f);
                drawSegment(0.05f, 0.25f);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q09");
    glutDisplayFunc(display);

#ifndef __APPLE__
    if (glewInit() == GLEW_OK)
        glutMainLoop();
#else
    glutMainLoop();
#endif

    return 0;
}
