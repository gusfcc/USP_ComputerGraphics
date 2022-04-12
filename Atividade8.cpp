// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085
#include <gl/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

GLfloat angle, fAspect;
int Bx[4], By[4], Bz[4];
GLdouble Px, Py, Pz;
int k = 0;

int nDots = 500;
double pacing = (double) 1/nDots;
double **mDots;

// Função calcula o valor do ponto ao longo da curva
// Recebe como parametro o eixo onde está calculando (variável 'C'), podendo ser no eixo X, Y e Z, e o valor de t.
float calculaPonto(char c, double t) {

	switch (c) {
	case 'x':
		return (pow(1 - t, 3) * Bx[0] + 3 * t * pow(1 - t, 2) * Bx[1] + 3 * pow(t, 2) * (1 - t) * Bx[2] + pow(t, 3) * Bx[3]);
		break;
	case 'y':
		return (pow(1 - t, 3) * By[0] + 3 * t * pow(1 - t, 2) * By[1] + 3 * pow(t, 2) * (1 - t) * By[2] + pow(t, 3) * By[3]);
		break;
	case 'z':
		return (pow(1 - t, 3) * Bz[0] + 3 * t * pow(1 - t, 2) * Bz[1] + 3 * pow(t, 2) * (1 - t) * Bz[2] + pow(t, 3) * Bz[3]);
		break;
	}
}

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Trilha
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < k; i++) {
		glVertex3d(mDots[0][i], mDots[1][i], mDots[2][i]);
	}
	glEnd();

	//Nave
	glPushMatrix();	
		glColor3f(0.0f, 0.0f, 1.0f);
		glTranslated(Px, Py, Pz);
		glutWireCube(1.0);
	glPopMatrix();
		

	// Desenha os pontos de controle na tela
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex3i(Bx[0], By[0], Bz[0]);
	glVertex3i(Bx[1], By[1], Bz[1]);
	glVertex3i(Bx[2], By[2], Bz[2]);
	glVertex3i(Bx[3], By[3], Bz[3]);
	glEnd();

	glutSwapBuffers();
}

void Inicializa(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	angle = 45;

	mDots = (double**)malloc(3 * sizeof(double*));
	for (int i = 0; i < 3; i++) mDots[i] = (double*)malloc(nDots * sizeof(double));
}

void Timer(int x) {
	
	Px = calculaPonto('x', (double)k*pacing);
	Py = calculaPonto('y', (double)k*pacing);
	Pz = calculaPonto('z', (double)k*pacing);
	mDots[0][k] = Px;
	mDots[1][k] = Py;
	mDots[2][k] = Pz;

	k++;

	if (k < nDots) {
		glutPostRedisplay();
		glutTimerFunc(10, Timer, x);
	}
}

void EspecificaParametrosVisualizacao(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, fAspect, 0.1, 500);
	glLineWidth(5);
	glPointSize(3);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(4, 3, 15, 4, 3, 0, 0, 1, 0);
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

	glutCreateWindow("Aula 8");

	glutTimerFunc(10, Timer, 0);

	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);

	//Entrada dos pontos pelo controle do usuario
	
	cout << "Digite as coordenadas X, Y, Z do primeiro pronto de controle:";
	cin >> Bx[0] >> By[0] >> Bz[0];

	cout << "Digite as coordenadas X, Y, Z do segundo pronto de controle:";
	cin >> Bx[1] >> By[1] >> Bz[1];

	cout << "Digite as coordenadas X, Y, Z do terceiro pronto de controle:";
	cin >> Bx[2] >> By[2] >> Bz[2];

	cout << "Digite as coordenadas X, Y, Z do quarto pronto de controle:";
	cin >> Bx[3] >> By[3] >> Bz[3];
	
	Inicializa();
	glutMainLoop();
}