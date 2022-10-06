/*
 *   UNIFESP SJC
 *
 *   COMPUTAÇÃO GRÁFICA
 *   OPENGL - INTERAÇÃO - EX FINAL
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
#define RETANGLE 2

const int WIDTH = 800, HEIGHT = 800;

float radius = 0;
float espessura = 2;
int start = 0;
int numClick = 0;
int limparTela = 0;
int figure = LINE;

float vColorGrey[] = {0.192, 0.192, 0.192};
float vColorBlack[] = {0.0, 0.0, 0.0};
float vColorRed[] = {1.0, 0.0, 0.0};
float vColorGreen[] = {0.0, 1.0, 0.0};
float vColorBlue[] = {0.0, 0.0, 1.0};
float vColorCyan[] = {0.0, 1.0, 1.0};
float vColorMagenta[] = {1.0, 0.0, 1.0};
float vColorYellow[] = {1.0, 1.0, 0.0};
float vColorBrown[] = {0.6, 0.42, 0.12};
float vColorOrange[] = {1.0, 0.7, 0.0};
float *vColor = vColorBlack;

typedef struct figLst {

    float pos1[2];
    float pos2[2];
    struct figLst *next;

}figLst;

figLst *head = NULL;

figLst* initFigure();
void deleteList();
void drawLine();
void drawCircumference();
void display();
void changeToLineFig();
void changeToCircFig();
void setCoords(int x, int y, float *posX, float *posY);
void setColor(unsigned char key, int x, int y);
void setEspessura(unsigned char key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

figLst* initFigure() {

    figLst *newFig = (figLst*) malloc(sizeof(figLst));
    newFig->next = NULL;
    return newFig;
}

void addNode() {

    figLst *newFig = initFigure();
    figLst *temp = head;

    if (head == NULL) {
        head = newFig;
    }

    else
    {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newFig;
    }
}

void deleteList() {

    figLst* current = head;
    figLst* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

void drawLine() {

    glLineWidth(espessura);
    glBegin(GL_LINES);

        glVertex2fv(head->pos1);
        glVertex2fv(head->pos2);

    glEnd();
    glutPostRedisplay();
}

void drawCircumference() {

    float theta;

    glLineWidth(espessura);
    glBegin(GL_LINE_LOOP);

        int i;
		for(i = 0; i <= 300; i++) {

            theta = 2 * PI * (float) i / (float) 300;
            glVertex2f(head->pos1[0] + (radius * cos(theta)), head->pos1[1] + (radius * sin(theta)));
		}

	glEnd();
    glutPostRedisplay();
}

void drawRetangle() {

    glLineWidth(espessura);
    glBegin(GL_LINE_LOOP);

        glVertex2f(head->pos1[0], head->pos1[1]);
        glVertex2f(head->pos1[0], head->pos2[1]);
        glVertex2f(head->pos2[0], head->pos2[1]);
        glVertex2f(head->pos2[0], head->pos1[1]);

    glEnd();
    glutPostRedisplay();
}

void display() {

    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3fv(vColor);

    if (start == 0)
        glClear(GL_COLOR_BUFFER_BIT);

    else {

        if (limparTela == 1) {
            glClear(GL_COLOR_BUFFER_BIT);
            deleteList();
        }

        else {

            if (figure == LINE && numClick == 0)
                drawLine();

            else if (figure == CIRC && numClick == 0)
                drawCircumference();

            else if (figure == RETANGLE && numClick == 0)
                drawRetangle();
        }
    }
    glutSwapBuffers();
}

void changeToLineFig() {

    figure = LINE;
    if (head != NULL)
        head->pos1[0] = head->pos1[1] = head->pos2[0] = head->pos2[1] = numClick = 0;
}

void changeToCircFig() {

    figure = CIRC;
    if (head != NULL)
        head->pos1[0] = head->pos1[1] = head->pos2[0] = head->pos2[1] = radius = numClick = 0;
}

void changeToRetangleFig() {

    figure = RETANGLE;
    if (head != NULL)
        head->pos1[0] = head->pos1[1] = head->pos2[0] = head->pos2[1] = numClick = 0;
}

void cleanScreen() {

    limparTela = 1;
    numClick = 0;
}

void setCoords(int x, int y, float *posX, float *posY) {

    *posX = 2 * (x / (float) WIDTH) - 1;
    *posY = (2 * ((y / (float) HEIGHT)) - 1) * -1;
}

void setColor(unsigned char key, int x, int y) {

    switch (key) {

        case '0': // CINZA
            vColor = vColorGrey;
            break;

        case '1': // PRETO
            vColor = vColorBlack;
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

        case 'E':
        case 'e':
            glutKeyboardFunc(setEspessura);
            break;

        case 'K':
        case 'k':
            glutKeyboardFunc(setColor);
            break;

        case 'R':
        case 'r':
            changeToLineFig();
            break;

        case 'C':
        case 'c':
            changeToCircFig();
            break;

        case 'B':
        case 'b':
            changeToRetangleFig();
            break;

        case 'L':
        case 'l':
            cleanScreen();
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void setEspessura(unsigned char key, int x, int y) {

    switch (key) {

        case '1': // ESPESSURA (1)
            espessura = 1;
            break;

        case '2': // ESPESSURA (2)
            espessura = 2;
            break;

        case '3': // ESPESSURA (3)
            espessura = 3;
            break;

        case '4': // ESPESSURA (4)
            espessura = 4;
            break;

        case '5': // ESPESSURA (5)
            espessura = 5;
            break;

        case '6': // ESPESSURA (6)
            espessura = 6;
            break;

        case '7': // ESPESSURA (7)
            espessura = 7;
            break;

        case '8': // ESPESSURA (8)
            espessura = 8;
            break;

        case '9': // ESPESSURA (9)
            espessura = 9;
            break;

        case 'E':
        case 'e':
            glutKeyboardFunc(setEspessura);
            break;

        case 'K':
        case 'k':
            glutKeyboardFunc(setColor);
            break;

        case 'R':
        case 'r':
            changeToLineFig();
            break;

        case 'C':
        case 'c':
            changeToCircFig();
            break;

        case 'B':
        case 'b':
            changeToRetangleFig();
            break;

        case 'L':
        case 'l':
            cleanScreen();
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        case 'E':
        case 'e':
            glutKeyboardFunc(setEspessura);
            break;

        case 'K':
        case 'k':
            glutKeyboardFunc(setColor);
            break;

        case 'R':
        case 'r':
            changeToLineFig();
            break;

        case 'C':
        case 'c':
            changeToCircFig();
            break;

        case 'B':
        case 'b':
            changeToRetangleFig();
            break;

        case 'L':
        case 'l':
            cleanScreen();
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        if (numClick == 0) {

            addNode();
            setCoords(x, y, &head->pos1[0], &head->pos1[1]);
        }

        else {
            setCoords(x, y, &head->pos2[0], &head->pos2[1]);
            limparTela = 0;
        }

        if (figure == CIRC)
            radius = sqrt(pow((head->pos2[0] - head->pos1[0]), 2) + pow((head->pos2[1] - head->pos1[1]), 2));

        if (numClick > 0)
            numClick = 0;

        else {
            numClick += 1;
            vColor = vColorBlack;
            start = 1;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Exercicio Final");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
 }
