#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// circle() is defined in main.cpp
extern void circle(float x, float y, float r);



float trainX = -2.5f;
float boatX = -1.5f;
float riverShift = 0.0f;
float cloudX = -0.8f;
float birdX = 1.2f;
const float groundLevel = -0.34f;


// OBJ-03: Clouds
void drawCloud(float x, float y, float scale)
{
    glColor3f(1.0, 1.0, 1.0);
    circle(x, y, 0.05 * scale);
    circle(x + 0.04 * scale, y + 0.02 * scale, 0.04 * scale);
    circle(x - 0.04 * scale, y + 0.01 * scale, 0.035 * scale);
}


// OBJ-04: Birds
void drawBird(float x, float y)
{
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x + 0.02, y - 0.01);
    glVertex2f(x + 0.04, y);
    glEnd();
}


// OBJ-05: Trees
void drawTree(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0);
    glColor3f(0.2, 0.1, 0.0);
    glRectf(-0.01, 0, 0.01, 0.12);
    glColor3f(0.0, 0.25, 0.0);
    circle(0, 0.15, 0.08);
    circle(-0.05, 0.11, 0.06);
    circle(0.05, 0.11, 0.06);
    glPopMatrix();
}



// OBJ-06: Houses
void drawHouse(float x, float y)
{
    glColor3f(0.7, 0.6, 0.4);
    glRectf(x, y, x + 0.18, y + 0.12);
    glColor3f(0.8, 0.9, 1.0);
    glRectf(x + 0.03, y + 0.04, x + 0.07, y + 0.08);
    glRectf(x + 0.11, y + 0.04, x + 0.15, y + 0.08);
    glColor3f(0.5, 0.1, 0.1);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.02, y + 0.12);
    glVertex2f(x + 0.09, y + 0.22);
    glVertex2f(x + 0.2, y + 0.12);
    glEnd();
}


// OBJ-01: Train
void drawTrain()
{
    glPushMatrix();
    glTranslatef(trainX, groundLevel, 0);
    glColor3f(0.1, 0.1, 0.1);
    glRectf(0.6, 0.05, 1.0, 0.25);
    glRectf(0.6, 0.25, 0.85, 0.32);
    glRectf(0.88, 0.25, 0.95, 0.35);
    glColor3f(0.6, 0.0, 0.0);
    glRectf(0.22, 0.05, 0.55, 0.22);
    glRectf(-0.15, 0.05, 0.18, 0.22);
    glColor3f(0, 0, 0);
    circle(0.7, 0.05, 0.05);
    circle(0.9, 0.05, 0.05);
    circle(0.3, 0.04, 0.04);
    circle(0.48, 0.04, 0.04);
    circle(-0.07, 0.04, 0.04);
    circle(0.1, 0.04, 0.04);
    glPopMatrix();
}


// OBJ-02: River Boat
void drawBoat()
{
    float bob = 0.015 * sin(riverShift * 0.5);
    glPushMatrix();
    glTranslatef(boatX, -0.75 + bob, 0);
    glColor3f(0.35, 0.18, 0.05);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15, 0);
    glVertex2f(0.15, 0);
    glVertex2f(0.22, 0.09);
    glVertex2f(-0.22, 0.09);
    glEnd();
    glColor3f(0.2, 0.1, 0.0);
    glRectf(-0.01, 0.09, 0.01, 0.28);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.01, 0.12);
    glVertex2f(0.15, 0.12);
    glVertex2f(0.01, 0.26);
    glEnd();
    glPopMatrix();
}


// OBJ-21: Sun
void drawSun()
{
    glColor3f(1.0, 0.9, 0.0);
    circle(0.75, 0.8, 0.1);
}


// OBJ-23: Sky
void drawSky()
{
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.8, 1.0);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glColor3f(0.9, 1.0, 1.0);
    glVertex2f(1, -0.1);
    glVertex2f(-1, -0.1);
    glEnd();
}


// OBJ-24: Mountains
void drawMountains()
{
    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.1, -0.1);
    glVertex2f(-0.4, 0.5);
    glVertex2f(0.3, -0.1);
    glEnd();
    glColor3f(0.0, 0.35, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1, -0.1);
    glVertex2f(0.8, 0.45);
    glVertex2f(1.4, -0.1);
    glEnd();
}


// OBJ-25: River
void drawRiver()
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.3, 0.6);
    glVertex2f(-1, -0.5);
    glVertex2f(1, -0.5);
    glColor3f(0.0, 0.2, 0.4);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();
}

// FN-09: updateScenario1() - advances Scenario 1's animation each frame
// Called from update() in main.cpp when currentScenario == 1
void updateScenario1()
{
    trainX += 0.01f;

    if (trainX > 1.2)
    {
        trainX = -2.5;
    }

    boatX += 0.004f;

    if (boatX > 1.3)
    {
        boatX = -1.5;
    }

    cloudX += 0.0015f;

    if (cloudX > 1.2)
    {
        cloudX = -1.5;
    }

    birdX -= 0.006f;

    if (birdX < -1.3)
    {
        birdX = 1.3;
    }

    riverShift += 0.1f;
}


// FN-04: runScenario1() - draws the rural scene by calling each object's
// Called from display() in main.cpp when currentScenario == 1
void runScenario1()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    drawSky();
    drawSun();
    drawCloud(cloudX, 0.85, 1.0);
    drawCloud(cloudX + 0.6, 0.78, 0.8);
    drawBird(birdX, 0.6);
    drawBird(birdX + 0.12, 0.55);
    drawMountains();
    glColor3f(0.1, 0.5, 0.1);
    glRectf(-1, -0.1, 1, -0.5);
    for (float x = -1.1; x <= 1.1; x += 0.12)
    {
        drawTree(x, -0.22, 0.7);
    }
    drawHouse(-0.7, -0.28);
    drawHouse(0.4, -0.28);
    glColor3f(0.2, 0.2, 0.2);
    glRectf(-1, groundLevel + 0.03, 1, groundLevel + 0.04);
    glRectf(-1, groundLevel - 0.01, 1, groundLevel);
    drawTrain();
    drawRiver();
    drawBoat();
}
