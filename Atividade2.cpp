// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085

#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

using namespace std;

extern int nStar = 0;

void Desenhar() {

    glViewport(0, 0, 500, 500);


    const double PI = 3.14159265358979323846;
    double moon_r = 50; //raio lua
    int nMoonDots = 100; // número de pontos lua
    double moon_x = 0, moon_y = 0; //valores do eixo x e y da lua
    double theta = 0, p = 0; //inicialização dos valores do angulo, periodo
    p = 2 * PI / nMoonDots; //período de rotação dos pontos
    theta = 2 * PI / nMoonDots; //valor atual do angulo
    double col = 0;
    
    glClear(GL_COLOR_BUFFER_BIT);

    //glColor3f(0.3, 0.6, 0.3);

    glBegin(GL_POLYGON);
    //Lua (com degrade)
    for (int i = 0; i <= nMoonDots; i++) {
        col = ((float)i / (nMoonDots * 1.15));
        glColor3f(0.93, 0.71, col);
        moon_x = moon_r * cos(theta) + 400; //equação paramétrica
        moon_y = moon_r * sin(theta) + 400; //equação paramétrica
        theta += p;
        glVertex2i(moon_x, moon_y);
    }
    glEnd();

    //Estrelas (pontos randomizados)
    double star_x = 0, star_y = 0;

    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    for (int i = 0; i < nStar; i++) {
        
        do{
            star_x = rand() % 500; //limite eixo x
            star_y = rand() % 492 + 11; //limite eixo y
        } while (star_x >= (400 - moon_r) && star_x <= (400 + moon_r) && star_y >= (400 - moon_r) && star_y <= (400 + moon_r)); //impedir que gere na lua

        glVertex2i(star_x, star_y);
    }
    glEnd();

    // Grama (parte do círculo)
    double grass_x = 0, grass_y = 0, nGrassDots = 1000;
    int grass_spacing = 10; //espaçamento entre as gramas
    double grass_r = 10; // raio do circulo das gramas
    p = PI/2 / nGrassDots; //período de rotação dos pontos
    theta = 2 * PI / nMoonDots; //valor atual do angulo

    for (int j = 0; j <= 500; j += grass_spacing) { //gerador de grama
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
            for (int i = 0; i <= nGrassDots; i++) { //gerador dos pontos individuais da grama
                col = ((float)i / (nGrassDots * 1.2));
                glColor3f(0, col, 0);
                grass_x = grass_r * cos(theta) + j; //equação paramétrica
                grass_y = grass_r * sin(theta) + 0; //equação paramétrica
                theta += p;

                glVertex2i(grass_x, grass_y);
            }
            theta = 2 * PI / nMoonDots;
            glEnd();
    }

    //Montanhas e neve das montanhas
    for (int i = 0; i < 4; i++) {
        glBegin(GL_POLYGON);
            glColor3f(0.4863, 0.3686, 0.2588);
            glVertex2i((125*i) -30, 10);
            glVertex2i((125 *(i+1)) +30, 10);
            glVertex2i((125 * (i + 1)) - 40, 140);
            glVertex2i((125 *i + 40), 140);
            
        glEnd();
        glBegin(GL_POLYGON);
            glColor3f(1,1,1);
            glVertex2i((125 * (i + 1)) - 40, 140);
            glVertex2i((125 * i + 40), 140);
            glVertex2i((((125 * i) + (125 * (i + 1))) / 2), 180);
            
        glEnd();
    }

    //Casa
    glBegin(GL_POLYGON);
        glColor3f(1, 0.992, 0.816);
        glVertex2i(190, 10);
        glVertex2i(190, 110);
        glVertex2i(310, 110);
        glVertex2i(310, 10);
    glEnd();

    //Porta
    glBegin(GL_POLYGON);
        glColor3f(0.5843, 0.2706, 0.2078);
        glVertex2i(200, 14);
        glVertex2i(200, 80);
        glVertex2i(235, 80);
        glVertex2i(235, 14);
    glEnd();

    //Escada
    glBegin(GL_POLYGON);
        glColor3f(0.5843, 0.6157, 0.6471);
        glVertex2i(195, 10);
        glVertex2i(195, 14);
        glVertex2i(240, 14);
        glVertex2i(240, 10);
    glEnd();

    //Janela
    glBegin(GL_POLYGON);
        glColor3f(0.5569, 0.6118, 0.7608);
        glVertex2i(245, 40);
        glVertex2i(245, 80);
        glColor3f(0.5373, 0.8118, 0.9412);
        glVertex2i(300, 80);
        glVertex2i(300, 40);
    glEnd();

    //Moldura vertical da janela
    glBegin(GL_POLYGON);
    glColor3f(0.8314, 0.6, 0.4235);
        glVertex2i(274.5, 80);
        glVertex2i(274.5, 40);
        glVertex2i(270.5, 40);
        glVertex2i(270.5, 80);

    glEnd();

    //Moldura horizontal da janela
    glBegin(GL_POLYGON);
        glColor3f(0.8314, 0.6, 0.4235);
        glVertex2i(245, 62);
        glVertex2i(245, 58);
        glVertex2i(300, 58);
        glVertex2i(300, 62);

    glEnd();

    //Telhado
    glBegin(GL_POLYGON);
        glColor3f(0.502, 0.0, 0.125);
        glVertex2i(175, 110);
        glVertex2i(325, 110);
        glVertex2i(250, 180);

    glEnd();


    glFlush();
}

void Inicializar() {
    glClearColor(0.2, 0.2, 0.2, 0.2);

    glLineWidth(3.0);

    glPointSize(2);

    gluOrtho2D(0, 500, 0, 500);
}



int main()
{
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(430, 130);

    glutCreateWindow("Hello World!");

    //Ler numero de estrelas
    cout << "Escreva o numero de estrelas no ceu: ";
    cin >> nStar;

    glutDisplayFunc(Desenhar);
    Inicializar();
    glutMainLoop();
}
