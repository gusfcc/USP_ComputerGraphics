// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

using namespace std;

typedef struct Head {
    GLint pos_x;
    GLint pos_y;
    int size;
} Head;

int matrixP[50][50] = {0};
char direction[2];
Head h;
int flag;

void Desenhar() {
    glViewport(0, 0, 500, 500);

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);
        glColor3f(0, 0.5, 0);
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++){
                if (matrixP[i][j] == -2) {
                    glBegin(GL_POINTS);
                        glColor3f(1, 0, 0);
                        glVertex2i(i, j);
                    glEnd();
                }
                else if (matrixP[i][j] == h.size) {
                    glBegin(GL_POINTS);
                        glColor3f(0, 0.5, 0);
                        glVertex2i(i, j);
                    glEnd();
                }
                else if (matrixP[i][j] > 0) {                    
                    glBegin(GL_POINTS);
                        glColor3f(0, 1, 0);
                        glVertex2i(i, j);
                    glEnd();
                }
                else if (matrixP[i][j] == -1) {
                    glBegin(GL_POINTS);
                        glColor3f(1, 1, 0);
                        glVertex2i(i, j);
                    glEnd();
                }
                
            }
        }

    glFlush();
}

void makeWall() {
    for (int i = 0; i < 50; i++) {
        matrixP[i][0] = -2;
        matrixP[i][49] = -2;
        matrixP[0][i] = -2;
        matrixP[49][i] = -2;
    }
}
void clearMap() {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            matrixP[i][j] = 0;
        }
    }
}

void Teclado (unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
    case 'R':
        flag = 1;
        clearMap();
        h.size = 1;
        h.pos_x = 25;
        h.pos_y = 25;
        matrixP[25][25] = 1;
        matrixP[35][25] = -1;
        direction[0] = 'd';
        direction[1] = 'd';
        makeWall();
        break;
    case 'w':
    case 'W':
        if (direction[0] != 's') {
            direction[0] = 'w';

        }
        break;
    case 'a':
    case 'A':
        if (direction[0] != 'd')
            direction[0] = 'a';
        break;
    case 's':
    case 'S':
        if (direction[0] != 'w') {
            direction[0] = 's';
        }
        break;
    case 'd':
    case 'D':
        if (direction[0] != 'a') {
            direction[0] = 'd';
        }
        break;
    default:
        break;
    }
}

void spawnFruit() {

    srand (time(NULL));
    int x = rand() % 47 + 1;
    int y = rand() % 47 + 1;

    while(true) {
        if (matrixP[x][y] > 0) {
            int x = rand() % 47 + 1;
            int y = rand() % 47 + 1;
        } else {
            matrixP[x][y] = -1;
            return;
        }
    }
}

int verifyMatrix() {
    if (matrixP[h.pos_x][h.pos_y] == -1) {
        h.size++;
        matrixP[h.pos_x][h.pos_y] = h.size;
        spawnFruit();
    } else if (matrixP[h.pos_x][h.pos_y] > 0 || (matrixP[h.pos_x][h.pos_y] == -2)){
        flag = 0;
    } else {
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                if (matrixP[i][j] > 0) {
                    matrixP[i][j] --;
                }
            }
        }
    }
    return 1;
}

void Timer (int aux){

    if (direction[1] == 'd' && flag == 1) {
        h.pos_x += 1;
        verifyMatrix();
        matrixP[h.pos_x][h.pos_y] = h.size;
        if (direction[0] != 'a') {
            direction[1] = direction[0];
        }
    }

    else if (direction[1] == 'a' && flag == 1) {
        h.pos_x -= 1;
        verifyMatrix();
        matrixP[h.pos_x][h.pos_y] = h.size;
        if (direction[0] != 'd') {
            direction[1] = direction[0];
        }
    }

    else if (direction[1] == 'w' && flag == 1) {
        h.pos_y -= 1;
        verifyMatrix();
        matrixP[h.pos_x][h.pos_y] = h.size;
        if (direction[0] != 's') {
            direction[1] = direction[0];
        }
    }

    else if (direction[1] == 's' && flag == 1) {
        h.pos_y += 1;
        verifyMatrix();
        matrixP[h.pos_x][h.pos_y] = h.size;
        if (direction[0] != 'w') {
            direction[1] = direction[0];
        }
    }

    /*
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            printf("%d ", matrixP[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */

    glutPostRedisplay();
    glutTimerFunc(80, Timer, aux);
}

void Inicializar() {
    
    flag = 1;
    h.size = 1;
    h.pos_x = 25;
    h.pos_y = 25;
    matrixP[25][25] = 1;
    matrixP[35][25] = -1;
    direction[0] = 'd';
    direction[1] = 'd';
    makeWall();

    glClearColor(0, 0, 0, 1);

    glLineWidth(3.0);

    glPointSize(10);

    gluOrtho2D(0, 50, 50, 0);
}



int main()
{
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(430, 130);

    glutCreateWindow("Gustavo e Renan");

    glutKeyboardFunc(Teclado);
    glutTimerFunc(80, Timer, 1);

    glutDisplayFunc(Desenhar);
    Inicializar();
    glutMainLoop();
}
