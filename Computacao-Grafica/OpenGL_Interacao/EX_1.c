/*
 *   UNIFESP SJC
 *
 *   COMPUTAÇÃO GRÁFICA
 *   OPENGL - INTERAÇÃO - EX 1
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

const int WIDTH = 1366, HEIGHT = 768;
float posX = 0.0, posY = 0.0;

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5);
    glBegin(GL_POINTS);

        glColor3f(0.0, 0.0 , 1.0);
        glVertex2f(posX, posY);

    glEnd();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        posX = (2 * ((float) x / (float) WIDTH)) - 1;
        posY = ((2 * ((float) y / (float) HEIGHT)) - 1) * -1;
        // printf("COORDENADAS: (%f, %f)\n", posX, posY);
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Exercicio 1");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
 }
