/*
 *   UNIFESP SJC
 *
 *   COMPUTAÇÃO GRÁFICA
 *   OPENGL - INTERAÇÃO - EX 5
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592654

#define LINE 0
#define CIRC 1

const int WIDTH = 1366, HEIGHT = 768;

float pos1[] = {0.0, 0.0};
float pos2[] = {0.0, 0.9};
float radius = 0;

float vColorGrey[] = {0.192, 0.192, 0.192};
float vColorWhite[] = {1.0, 1.0, 1.0};
float vColorRed[] = {1.0, 0.0, 0.0};
float vColorGreen[] = {0.0, 1.0, 0.0};
float vColorBlue[] = {0.0, 0.0, 1.0};
float vColorCyan[] = {0.0, 1.0, 1.0};
float vColorMagenta[] = {1.0, 0.0, 1.0};
float vColorYellow[] = {1.0, 1.0, 0.0};
float vColorBrown[] = {0.6, 0.42, 0.12};
float vColorOrange[] = {1.0, 0.7, 0.0};

float *vColor = vColorBlue;
int numClick = 0;
int figure = LINE;

void drawLine() {

    glBegin(GL_LINES);

        glVertex2fv(pos1);
        glVertex2fv(pos2);

    glEnd();
    glutPostRedisplay();
}

void drawCircumference() {

    float theta;
    glBegin(GL_LINE_LOOP);

        int i;
		for (i = 0; i <= 300; i++) {

            theta = 2 * PI * (float) i / (float) 300;
            glVertex2f(pos2[0] + (radius * cos(theta)), pos2[1] + (radius * sin(theta)));
		}

	glEnd();
    glutPostRedisplay();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(vColor);

    if (figure == LINE && numClick == 0)
        drawLine();

    else if (figure == CIRC && numClick == 0)
        drawCircumference();

    glutSwapBuffers();
}

void changeToLineFig() {

    figure = LINE;
    pos1[0] = pos1[1] = pos2[0] = pos2[1] = numClick = 0;
}

void changeToCircFig() {

    figure = CIRC;
    pos1[0] = pos1[1] = pos2[0] = pos2[1] = radius = numClick = 0;
}

void setCoords(int x, int y, float *posX, float *posY) {

    *posX = (2 * ((float) x / (float) WIDTH)) - 1;
    *posY = ((2 * ((float) y / (float) HEIGHT)) - 1) * -1;
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        case '0': // CINZA
            vColor = vColorGrey;
            break;

        case '1': // BRANCO
            vColor = vColorWhite;
            break;

        case '2': // VERMELHO
            vColor = vColorRed;
            break;

        case '3': // VERDE
            vColor = vColorGreen;
            break;

        case '4': // AZUL
            vColor = vColorBlue;
            break;

        case '5': // CIANO
            vColor = vColorCyan;
            break;

        case '6': // MAGENTA
            vColor = vColorMagenta;
            break;

        case '7': // AMARELO
            vColor = vColorYellow;
            break;

        case '8': // MARROM
            vColor = vColorBrown;
            break;

        case '9': // LARANJA
            vColor = vColorOrange;
            break;

        case 'R':
        case 'r':
            changeToLineFig();
            break;

        case 'C':
        case 'c':
            changeToCircFig();
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        if (numClick == 0)
            setCoords(x, y, &pos1[0], &pos1[1]);

        else
            setCoords(x, y, &pos2[0], &pos2[1]);

        if (figure == CIRC)
            radius = sqrt(pow((pos2[0] - pos1[0]), 2) + pow((pos2[1] - pos1[1]), 2));

        if (numClick > 0)
            numClick = 0;

        else
            numClick += 1;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Exercicio 5");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
 }
