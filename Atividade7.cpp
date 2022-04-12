// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085

#include <gl/glut.h>
#include <math.h>
#include "Atividade1.h"

GLfloat angle, fAspect;
GLfloat anguloRotacao = 0;

void Desenha(void)
{
	double PI = 3.14159265359;
	double radAngle = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
		glRotated(anguloRotacao, 0, 0, 1);
		glutWireSphere(30, 20, 20);
	glPopMatrix();
	
	radAngle = anguloRotacao * PI / 180.0;

	glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glTranslated(75 * sin(radAngle), 75 * cos(radAngle), 0);
		glTranslated(0, 0, 0);
		glRotated(-anguloRotacao, 0, 0, 1);
		glutWireSphere(10, 15, 15);
	glPopMatrix();



	glutSwapBuffers();
}

void Inicializa(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

	gluLookAt(0, 150, 250, 0, 0, 0, 0, 0, 1);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(350, 300);

	glutCreateWindow("Aula 7");

	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);

	// Define a função timer ==============
	glutTimerFunc(30, Timer, 1);
	// ====================================

	Inicializa();
	glutMainLoop();
}