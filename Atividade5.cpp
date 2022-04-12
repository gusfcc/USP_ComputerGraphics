// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

using namespace std;

int flag = 0;

GLint posMaoE_X = 150;
GLint posMaoE_Y = 150;

GLint posMaoD_X = 260;
GLint posMaoD_Y = 120;

void desenhaMaosE(){
    glBegin(GL_LINES);
        glVertex2i(150, 250);
        glVertex2i(200, 250);
    glEnd();
}
void desenhaMaosD(){
    glBegin(GL_LINES);
        glVertex2i(300, 250);
        glVertex2i(350, 250);
    glEnd();
}
void desenhaBracosE(){
    glBegin(GL_LINES);
        glVertex2i(200, 250);
        glVertex2i(250, 250);
    glEnd();
}

void desenhaBracosD(){
    glBegin(GL_LINES);
        glVertex2i(300, 250);
        glVertex2i(250, 250);
    glEnd();
}

void Desenhar() {

    glViewport(0, 0, 500, 500);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    
    
    double PI = 3.141592653;
    double r = 35;
    int nDots = 500;
    double x = 0, y = 0, theta = 0, p = 0;
    p = 2 * PI / nDots;
    theta = 2 * PI / nDots;
    glBegin(GL_POLYGON);
    for (int i = 0; i < nDots; i++) {
        x = r * cos(theta);
        y = r * sin(theta);
        theta += p;
        glVertex2i(x + 250, y + 170);
    }
    glEnd();

    //tronco
    glBegin(GL_LINES);
    glVertex2i(250, 200);
    glVertex2i(250, 350);
    glEnd();

    //pernas
    glBegin(GL_LINES);
    glVertex2i(250, 350);
    glVertex2i(200, 500);

    glVertex2i(250, 350);
    glVertex2i(300, 500);
    glEnd();
    
    if (flag == 0) {
        //maos
        desenhaMaosE();
        desenhaMaosD();

        //bracos
        desenhaBracosE();
        desenhaBracosD();
    }
    else if (flag == 1) {
        //maos
        glPushMatrix();
            glTranslated(200, 250, 0);
            glRotated(45, 0, 0, 1);
            glTranslated(-200, -250, 0);
            desenhaMaosE();
        glPopMatrix();

        glPushMatrix();
            glTranslated(300, 250, 0);
            glRotated(-45, 0, 0, 1);
            glTranslated(-300, -250, 0);
            desenhaMaosD();
        glPopMatrix();

        //bracos
        desenhaBracosE();
        desenhaBracosD();
    }
    else if (flag == 2) {
        //maos
        glPushMatrix();
            glTranslated(215, 215, 0);
            glRotated(45, 0, 0, 1);
            glTranslated(-200, -250, 0);
            desenhaMaosE();
        glPopMatrix();

        glPushMatrix();
            glTranslated(285, 215, 0);
            glRotated(-45, 0, 0, 1);
            glTranslated(-300, -250, 0);
            desenhaMaosD();
        glPopMatrix();

        //bracos
        glPushMatrix();
            glTranslated(250, 250, 0);
            glRotated(45, 0, 0, 1);
            glTranslated(-250, -250, 0);
            desenhaBracosE();
        glPopMatrix();

        glPushMatrix();
            glTranslated(250, 250, 0);
            glRotated(-45, 0, 0, 1);
            glTranslated(-250, -250, 0);
            desenhaBracosD();
        glPopMatrix();
    }


    glFlush();
}

void Timer(int value) {
    if (value == 0) { flag = 0; }
    if (value == 1) { flag = 1; }
    if (value == 2) { flag = 2; }
    if (value == 3) { flag = 1; value = -1; }
    

    glutPostRedisplay();
    glutTimerFunc(300, Timer, value + 1);
}


void Inicializar() {
    glClearColor(1, 1, 1, 1);

    glLineWidth(3.0);

    glPointSize(5);

    gluOrtho2D(0, 500, 500, 0);
}



int main()
{
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(430, 130);

    glutCreateWindow("Gustavo e Renan");

    glutTimerFunc(300, Timer, 0);

    glutDisplayFunc(Desenhar);
    Inicializar();
    glutMainLoop();
}
