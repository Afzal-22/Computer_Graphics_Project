#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int currentScenario = 1;


extern void runScenario1();
extern void runScenario2();
extern void runScenario3();

extern void updateScenario1();   // FN-09 (Scenario 1 motion)
extern void updateScenario2();   // FN-07/10/11/12 (Scenario 2 motion)
extern void updateScenario3();   // FN-08/13/14 (Scenario 3 motion)

extern void initScenario2();     // seeds Scenario 2's random bubbles
extern void initScenario3();     // seeds Scenario 3's random stars

extern void startScenario2();        // Scenario 2: 'P' key
extern void liftScenario2Anchor();   // Scenario 2: 'L' key

// Used to draw OBJ-21 (Sun), OBJ-22 (Moon), and as a sub-shape
// inside OBJ-01 (Train wheels) and OBJ-11 (Starfish body)
void circle(float x, float y, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++)
    {
        float ang = i * 3.1416f / 180;
        glVertex2f(x + cos(ang) * r, y + sin(ang) * r);
    }
    glEnd();
}


// FN-01: display() - renders whichever scenario is currently active
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentScenario == 1)
    {
        runScenario1();
    }
    else if (currentScenario == 2)
    {
        runScenario2();
    }
    else if (currentScenario == 3)
    {
        runScenario3();
    }

    glutSwapBuffers();
}


// FN-02: keyboard() - switches scenarios with 1 / 2 / 3, and handles
// Scenario 2's extra controls (P = start, L = lift anchor)
void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
    {
        currentScenario = 1;
    }

    if (key == '2')
    {
        currentScenario = 2;
    }

    if (key == '3')
    {
        currentScenario = 3;
    }

    if (currentScenario == 2)
    {
        if (key == 'p' || key == 'P')
        {
            startScenario2();
        }

        if (key == 'l' || key == 'L')
        {
            liftScenario2Anchor();
        }
    }

    glutPostRedisplay();
}

// FN-03: update()
void update(int value)
{
    if (currentScenario == 1)
    {
        updateScenario1();
    }
    else if (currentScenario == 2)
    {
        updateScenario2();
    }
    else if (currentScenario == 3)
    {
        updateScenario3();
    }

    glutPostRedisplay();

    glutTimerFunc(16, update, 0);
}


// main() - window setup, random seeding, GLUT callback wiring
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("Press 1, 2 or 3");

    srand(time(NULL));
    initScenario2();
    initScenario3();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}
