// Teste.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

using namespace std;

extern int nDots = 0;
extern double r = 0;

void Desenhar() {

    glViewport(0, 0, 500, 500);


    const double PI = 3.14159265358979323846;
    // double r = 100; //raio
    // int nDots = 50; // número de pontos
    double x = 0, y = 0, theta = 0, p = 0; //inicialização dos valores do eixo x, y, angulo, periodo
    p = 2 * PI / nDots; //período de rotação dos pontos
    theta = 2 * PI / nDots; //valor atual do angulo
    double col = 0;


    glClear(GL_COLOR_BUFFER_BIT);

    //glColor3f(0.3, 0.6, 0.3);

    glBegin(GL_POLYGON);
    //circle
    for (int i = 0; i <= nDots; i++) {
        col = ((float)i / (nDots*1.15));
        glColor3f(0.93, 0.71, col);
        x = r * cos(theta); //equação paramétrica
        y = r * sin(theta); //equação paramétrica
        theta += p;
        glVertex2i(x, y);
    }

    glEnd();

    glFlush();
}

void Inicializar() {
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(3.0);

    glPointSize(2);

    gluOrtho2D(-500, 500, -500, 500);
}



int main()
{
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(430, 130);

    glutCreateWindow("Hello World!");

    //Leitura de nDots
    cout << "Digite o numero de pontos: ";
    cin >> nDots;

    //Leitura do raio r
    cout << "Digite o tamanho do raio: ";
    cin >> r;

    glutDisplayFunc(Desenhar);
    Inicializar();
    glutMainLoop();
}
