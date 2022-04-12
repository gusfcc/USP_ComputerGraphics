// Gustavo Fernandes Carneiro de Castro - 11369684
// Renan Gomes Carneiro de Freitas - 11391085

#include <stdio.h>
#include <iostream>
#include <gl/glut.h>

using namespace std;

GLfloat angle, fAspect;
GLfloat cam_pos_x, cam_pos_y, target_pos_x;

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 1.0f);

	//Desenha o teapot com a cor corrente (wire-frame)
	glutWireTeapot(50.0f);
	glutSwapBuffers();
}


void Inicializa(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	angle = 45;
	cam_pos_x = 0;
	cam_pos_y = 80;
	target_pos_x = 0;

}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle, fAspect, 0.1, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(cam_pos_x, cam_pos_y, 200, target_pos_x, 0, 0, 0, 1, 0);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLint largura, GLint altura)
{
	// Para previnir uma divisão por zero
	if (altura == 0) altura = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, largura, altura);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)largura / (GLfloat)altura;

	EspecificaParametrosVisualizacao();
}

void Setinhas(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		cam_pos_x -= 10;
	}
	else if (key == GLUT_KEY_RIGHT) {
		cam_pos_x += 10;
	}
	else if (key == GLUT_KEY_DOWN) {
		cam_pos_y -= 10;
	}
	else if (key == GLUT_KEY_UP) {
		cam_pos_y += 10;
	}

	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void Click(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		target_pos_x -= 10;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		target_pos_x += 10;
	}

	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(350, 300);

	glutCreateWindow("Aula 6");
	glutSpecialFunc(Setinhas);
	glutMouseFunc(Click);

	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela); // Função para ajustar o tamanho da tela
	Inicializa();
	glutMainLoop();
}