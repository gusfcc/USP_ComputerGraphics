// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085

#include <gl/glut.h>
#include <math.h>
#include "Atividade1.h"

GLfloat angle, fAspect;
GLfloat anguloRotacao = 0;

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	double PI = 3.14159265359;
	double radAngle = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0.5, 1);
	glPushMatrix();
	glRotated(anguloRotacao, 0, 0, 1);
	glutSolidSphere(30, 20, 20);
	glPopMatrix();

	radAngle = anguloRotacao * PI / 180.0;

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(75 * sin(radAngle), 75 * cos(radAngle), 0);
	glTranslated(0, 0, 0);
	glRotated(-anguloRotacao, 0, 0, 1);
	glutSolidSphere(10, 15, 15);
	glPopMatrix();

	glutSwapBuffers();
}

void Inicializa(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	GLfloat luzAmbiente[4] = { 0,0,0,1 };
	GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };
	GLfloat luzEspecular[4] = { 0.2, 0.2, 0.2, 1.0 }; // geralmente branco ou cinza
	GLfloat posicaoLuz[4] = {0.1, -400, 0.1, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0, 1.0,1.0,1.0 }; // define a cor do brilho no material, geralmente branco
	GLint expoenteEspecular = 60; // define o brilho do material. varia de 0-128

	// Especifica que a cor de fundo da janela será preta
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, expoenteEspecular);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	angle = 45;
}

void Timer(int value) {
	anguloRotacao = value % 360;
	glutPostRedisplay();
	glutTimerFunc(30, Timer, value + 1);
}

void EspecificaParametrosVisualizacao(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, fAspect, 0.1, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0.1, 300, 0, 0, 0, 0, 0, 1);
}

void AlteraTamanhoJanela(GLint largura, GLint altura)
{
	if (altura == 0) altura = 1;

	glViewport(0, 0, largura, altura);

	fAspect = (GLfloat)largura / (GLfloat)altura;

	EspecificaParametrosVisualizacao();
}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(350, 300);

	glutCreateWindow("Gustavo e Renan");

	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);

	// Define a função timer ==============
	glutTimerFunc(30, Timer, 1);
	// ====================================

	Inicializa();
	glutMainLoop();
}