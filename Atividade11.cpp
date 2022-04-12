// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085

#include <gl/glut.h>
#include <math.h>
#include "Atividade1.h"
#include <stdio.h>
#include "glaux.h" 

#pragma warning(disable:4996)
#pragma comment(lib, "legacy_stdio_definitions.lib")

using namespace std;


GLfloat angle, fAspect;
GLfloat anguloRotacao = 0;
GLfloat obsX = 0.1;
GLfloat obsY = 0.1;
GLfloat obsZ = 300;
GLfloat alvoX = 0;
GLfloat alvoY = 0;
GLfloat alvoZ = 0;
GLfloat vetX = 0;
GLfloat vetY = 1;
GLfloat vetZ = 0;
int rot = 0;
int rotZ = 0;
double PI = 3.14159265359;
GLuint idTexturaTerra;
GLuint idTexturaLua;
AUX_RGBImageRec* texturaTerra;
AUX_RGBImageRec* texturaLua;

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	GLUquadric* qTerra = gluNewQuadric();
	GLUquadric* qLua = gluNewQuadric();

	double PI = 3.14159265359;
	double radAngle = 0;	

	glBindTexture(GL_TEXTURE_2D, idTexturaTerra);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texturaTerra->sizeX,
		texturaTerra->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
		texturaTerra->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	gluQuadricTexture(qTerra, TRUE);
	gluQuadricNormals(qTerra, GLU_SMOOTH);

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
		glRotated(anguloRotacao, 0, 0, 1);
		gluSphere(qTerra, 30, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	radAngle = anguloRotacao * PI / 180.0;

	glBindTexture(GL_TEXTURE_2D, idTexturaLua);	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texturaLua->sizeX,
		texturaLua->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
		texturaLua->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	gluQuadricTexture(qLua, TRUE);
	gluQuadricNormals(qLua, GLU_SMOOTH);

	glPushMatrix();
	
	glEnable(GL_TEXTURE_2D);
		glTranslated(75 * sin(radAngle), 75 * cos(radAngle), 0);
		glTranslated(0, 0, 0);
		glRotated(-anguloRotacao, 0, 0, 1);
		gluSphere(qLua, 10, 15, 15);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
}

AUX_RGBImageRec* LoadBMP(const char* Filename) {
	FILE* File = NULL;
	if (!Filename) {
		return NULL;
	}
	File = fopen(Filename, "r");
	if (File)	// Se o arquivo existe
	{
		fclose(File);
		return auxDIBImageLoadA(Filename);//Retorna a imagem
	}
	return NULL;
}

void Inicializa(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	GLfloat luzAmbiente[4] = { 0.1, 0.1, 0.1,1 };
	GLfloat luzDifusa[4] = { 0.8,0.8,0.8,1.0 };
	GLfloat luzEspecular[4] = { 0.2, 0.2, 0.2, 1.0 }; // geralmente branco ou cinza
	GLfloat posicaoLuz[4] = { 0.1, -400, 0.1, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0, 1.0,1.0,1.0 }; // define a cor do brilho no material, geralmente branco
	GLint expoenteEspecular = 60; // define o brilho do material. varia de 0-128

	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
	
	// Comandos de inicialização para textura
	texturaTerra = LoadBMP("C:/Code/CompGraf/TexturaPlanetas/terra.bmp");
	glGenTextures(1, &idTexturaTerra);

	texturaLua = LoadBMP("C:/Code/CompGraf/TexturaPlanetas/lua.bmp");
	glGenTextures(1, &idTexturaLua);
	
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

	//gluLookAt(obsX, obsY, obsZ, alvoX, alvoY, alvoZ, vetX, vetY, vetZ);
	gluLookAt(obsX, obsY, obsZ, alvoX, alvoY, alvoZ, vetX, vetY, vetZ);
}

void AlteraTamanhoJanela(GLint largura, GLint altura)
{
	if (altura == 0) altura = 1;

	glViewport(0, 0, largura, altura);

	fAspect = (GLfloat)largura / (GLfloat)altura;

	EspecificaParametrosVisualizacao();
}

void GerenciaMouse(int button, int state, int x, int y) {
	double radAngle = 0;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

		rot = (rot + 10) % 360;
		radAngle = rot * PI / 180.0;

		vetX = sin(radAngle);
		vetY = cos(radAngle);

	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		rot = (rot - 10) % 360;
		radAngle = rot * PI / 180.0;

		vetX = sin(radAngle);
		vetY = cos(radAngle);

	}

	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


void GerenciaTeclado(unsigned char key, int x, int y) {
	double radAngle = 0;
	switch (key) {
	case ' ': // restaura posição inicial da camera
		obsX = 0.1;
		obsY = 0.1;
		obsZ = 300;
		alvoX = 0;
		alvoY = 0;
		alvoZ = 0;
		vetX = 0;
		vetY = 1;
		vetZ = 0;
		rot = 0;
		rotZ = 0;
		break;
		// movimentacao do observador
	case 'd':
		obsX = obsX + 50;
		break;
	case 'a':
		obsX = obsX - 50;
		break;
	case 'w':
		obsZ = obsZ - 50;
		break;
	case 's':
		obsZ = obsZ + 50;
		break;
	case 'q':
		obsY = obsY + 50;
		break;
	case 'e':
		obsY = obsY - 50;
		break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) {
		alvoY = alvoY + 50;
	}
	if (key == GLUT_KEY_DOWN) {
		alvoY = alvoY - 50;
	}
	if (key == GLUT_KEY_RIGHT) {
		alvoX = alvoX + 50;
	}
	if (key == GLUT_KEY_LEFT) {
		alvoX = alvoX - 50;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(350, 300);

	glutCreateWindow("Gustavo e Renan");

	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);

	glutMouseFunc(GerenciaMouse); // Define qual funcao gerencia o comportamento do mouse
	glutKeyboardFunc(GerenciaTeclado); // Define qual funcao gerencia o comportamento do teclado
	glutSpecialFunc(TeclasEspeciais); // Define qual funcao gerencia as teclas especiais

	// Define a função timer ==============
	glutTimerFunc(30, Timer, 1);
	// ====================================

	Inicializa();
	glutMainLoop();
}