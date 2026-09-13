#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// circle() is defined in main.cpp and shared by all scenario files
extern void circle(float x, float y, float r);


float tShipX = -1.4f;
float tShipY = -0.1f;
float sink = 0.0f;
float tAngle = 0.0f;
float wave = 0.0f;
bool hit = false;
float starX[120], starY[120];


// OBJ-19: Stars
void stars()
{
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.5);
    glBegin(GL_POINTS);
    for (int i = 0; i < 120; i++)
    {
        glVertex2f(starX[i], starY[i]);
    }
    glEnd();
}


// OBJ-20: Sea Surface
void sea()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POLYGON);
    for (float x = -1; x <= 1; x += 0.02)
    {
        float waveHeight = -0.3 + sin(x * 10 + wave) * 0.02;
        glColor4f(0.0, 0.1, 0.35, 0.7);
        glVertex2f(x, waveHeight);
    }
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();
    glDisable(GL_BLEND);
}


// OBJ-27: Night Sky
void nightSky()
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.05);
    glVertex2f(-1, 1);
    glColor3f(0.0, 0.0, 0.05);
    glVertex2f(1, 1);
    glColor3f(0.05, 0.05, 0.2);
    glVertex2f(1, -0.3);
    glColor3f(0.05, 0.05, 0.2);
    glVertex2f(-1, -0.3);
    glEnd();
}


// OBJ-22: Moon
void moon()
{
    glColor3f(0.92, 0.92, 0.88);
    circle(-0.7, 0.75, 0.1);
}


// OBJ-18: Iceberg
void iceberg()
{
    glBegin(GL_POLYGON);
    glColor3f(0.85, 0.92, 1.0);
    glVertex2f(0.75, 0.25);
    glVertex2f(0.9, 0.1);
    glColor3f(0.4, 0.6, 0.8);
    glVertex2f(0.85, -0.3);
    glVertex2f(0.6, -0.3);
    glVertex2f(0.6, 0.05);
    glEnd();
}


// Helper for OBJ-17 (Titanic Ship) - draws one chimney
void drawChimney(float x, float y)
{
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.5, 0.1);
    glVertex2f(x, y);
    glVertex2f(x + 0.04, y);
    glColor3f(0.9, 0.6, 0.2);
    glVertex2f(x + 0.04, y + 0.13);
    glVertex2f(x, y + 0.13);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(x, y + 0.1);
    glVertex2f(x + 0.04, y + 0.1);
    glVertex2f(x + 0.04, y + 0.13);
    glVertex2f(x, y + 0.13);
    glEnd();
}


// OBJ-17: Titanic Ship
void ship()
{
    glPushMatrix();
    glTranslatef(tShipX, tShipY - sink, 0);
    glRotatef(-tAngle, 0, 0, 1);
    glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.55, -0.1);
    glVertex2f(0.55, -0.1);
    glVertex2f(0.5, -0.2);
    glVertex2f(-0.5, -0.2);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.05, 0.05, 0.05);
    glVertex2f(-0.55, -0.1);
    glVertex2f(0.55, -0.1);
    glColor3f(0.15, 0.15, 0.15);
    glVertex2f(0.6, 0.1);
    glVertex2f(-0.6, 0.1);
    glEnd();
    glColor3f(0.95, 0.95, 0.9);
    glBegin(GL_QUADS);
    glVertex2f(-0.5, 0.1);
    glVertex2f(0.5, 0.1);
    glVertex2f(0.45, 0.18);
    glVertex2f(-0.45, 0.18);
    glEnd();
    glColor3f(0.9, 0.9, 0.85);
    glBegin(GL_QUADS);
    glVertex2f(-0.35, 0.18);
    glVertex2f(0.35, 0.18);
    glVertex2f(0.3, 0.25);
    glVertex2f(-0.3, 0.25);
    glEnd();
    for (float i = -0.45; i <= 0.45; i += 0.09)
    {
        glColor3f(1.0, 0.9, 0.3);
        circle(i, 0.02, 0.012);
    }
    for (float i = -0.28; i <= 0.25; i += 0.06)
    {
        glColor3f(1.0, 0.9, 0.2);
        glBegin(GL_QUADS);
        glVertex2f(i, 0.2);
        glVertex2f(i + 0.03, 0.2);
        glVertex2f(i + 0.03, 0.23);
        glVertex2f(i, 0.23);
        glEnd();
    }
    drawChimney(-0.16, 0.25);
    drawChimney(-0.05, 0.25);
    drawChimney(0.06, 0.25);
    drawChimney(0.17, 0.25);
    glColor3f(0.1, 0.1, 0.1);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.4, 0.18);
    glVertex2f(-0.4, 0.42);
    glVertex2f(0.35, 0.25);
    glVertex2f(0.35, 0.4);
    glEnd();
    glPopMatrix();
}


// random positions in the night sky
void initScenario3()
{
    for (int i = 0; i < 120; i++)
    {
        starX[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        starY[i] = ((float)rand() / RAND_MAX) * 0.7f + 0.3f;
    }
}


//Called from update() in main.cpp when currentScenario == 3
void updateScenario3()
{
    // FN-14: Wave animation
    wave += 0.05;
    // FN-13: Ship approach & collision check
    if (!hit)
    {
        tShipX += 0.005;
        if (tShipX >= 0.15) hit = true;
    }
    // FN-08: Sinking/rotation logic
    else
    {
        sink += 0.0012;
        tAngle += 0.07;
    }
}


// FN-06: runScenario3()
// Called from display() in main.cpp when currentScenario == 3
void runScenario3()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    nightSky();
    moon();
    stars();
    iceberg();
    ship();
    sea();
}
