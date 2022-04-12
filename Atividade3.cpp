// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

using namespace std;

int matrixP[500][500];
int col = 1;
int mFlag = 0;

void Desenhar() {

    glViewport(0, 0, 500, 500);

    glClear(GL_COLOR_BUFFER_BIT);


    for (int y = 0; y < 500; y++) {
        for (int x = 0; x < 500; x++) {
            glBegin(GL_POINTS);
            if (matrixP[x][y] != 0) {

                if(matrixP[x][y] == 1 ) // default && W (white)
                    glColor3f(1, 1, 1);

                if(matrixP[x][y] == 2) // R (red)
                    glColor3f(1, 0, 0);

                if(matrixP[x][y] == 3) // G (green)
                    glColor3f(0, 1, 0);

                if(matrixP[x][y] == 4) // B (blue)
                    glColor3f(0, 0, 1);

                if(matrixP[x][y] == 5) // B (black)
                    glColor3f(0, 0, 0);
                
                glVertex2i(x, y);
            }
            glEnd();
        }
    }
    glFlush();
}

void Teclado (unsigned char key, int x, int y) {
    
    switch (key) {
        case 'C':
        case 'c':
            for (int y = 0; y < 500; y++) {
                for (int x = 0; x < 500; x++) {
                    matrixP[x][y] = 0;
                }
            }
            break;
        case 'R':
        case 'r':
            col = 2;
            break;
        case 'G':
        case 'g':
            col = 3;
            break;
        case 'B':
        case 'b':
            col = 4;
            break;
        case 'W':
        case 'w':
            col = 1;
            break;
        case 'X':
        case 'x':
            col = 5;
            break;

        
    }
    glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {       
        matrixP[x][y] = col;
        mFlag = 1;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        mFlag = 0;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        for (int i = -20; i < 20; i++) {
            for (int j = -20; j < 20; j++) {
                matrixP[x + j][y + i] = 0;
            }
        }
        mFlag = 2;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        mFlag = 0;
    }

    glutPostRedisplay();
}

void Movimento(int x, int y) {
    if (mFlag == 1) {
        matrixP[x][y] = col;
        glutPostRedisplay();
    }

    else if (mFlag == 2) {
        for (int i = -20; i < 20; i++) {
            for (int j = -20; j < 20; j++) {
                matrixP[x + j][y + i] = 0;
            }
        }
        glutPostRedisplay();
    }
}


void Inicializar() {
    glClearColor(0.0, 0.5, 0.2, 1);

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

    glutKeyboardFunc(Teclado);
    glutMouseFunc(Mouse);
    glutMotionFunc(Movimento);

    glutDisplayFunc(Desenhar);
    Inicializar();
    glutMainLoop();
}
