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

float pos1[2] = {0.0, 0.0};
float pos2[2] = {0.0, 0.0};

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
    float *vColor;
    float espessura;
    float radius;
    int figure;
    struct figLst *next;

}figLst;

void addNode();
void printList();
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

figLst *head = NULL;
figLst *last = NULL;

void addNode() {

    figLst *newFig = (figLst*) malloc(sizeof(figLst));

    newFig->pos1[0] = pos1[0];
    newFig->pos1[1] = pos1[1];
    newFig->pos2[0] = pos2[0];
    newFig->pos2[1] = pos2[1];
    newFig->vColor = vColor;
    newFig->espessura = espessura;
    newFig->radius = radius;
    newFig->figure = figure;
    newFig->next = NULL;

    if (head == NULL) {
        head = newFig;
        last = head;
    }

    else
    {
        figLst *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newFig;
        last = temp->next;
    }
}

void printList() {

   figLst *ptr = head;
   printf("\n[ HEAD ->\n");

   char *typeFigure[] = {"LINE", "CIRC", "RETANGLE"};

   while(ptr != NULL) {
      printf("(%f, %f) - (%f, %f) - %s\n", ptr->pos1[0], ptr->pos1[1], ptr->pos2[0], ptr->pos2[1], typeFigure[ptr->figure]);
      ptr = ptr->next;
   }

   printf(" -> TAIL ]\n");
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
    head = NULL;
    last = NULL;
}

void drawLine(figLst *p) {

    glLineWidth(p->espessura);
    glBegin(GL_LINES);

        glVertex2fv(p->pos1);
        glVertex2fv(p->pos2);

    glEnd();
    glutPostRedisplay();
}

void drawCircumference(figLst *p) {

    float theta;

    glLineWidth(p->espessura);
    glBegin(GL_LINE_LOOP);

        int i;
		for(i = 0; i <= 300; i++) {

            theta = 2 * PI * (float) i / (float) 300;
            glVertex2f(p->pos1[0] + (p->radius * cos(theta)), p->pos1[1] + (p->radius * sin(theta)));
		}

	glEnd();
    glutPostRedisplay();
}

void drawRetangle(figLst *p) {

    glLineWidth(p->espessura);
    glBegin(GL_LINE_LOOP);

        glVertex2f(p->pos1[0], p->pos1[1]);
        glVertex2f(p->pos1[0], p->pos2[1]);
        glVertex2f(p->pos2[0], p->pos2[1]);
        glVertex2f(p->pos2[0], p->pos1[1]);

    glEnd();
    glutPostRedisplay();
}

void display() {

    glClearColor(1.0, 1.0, 1.0, 0);

    if (start == 0)
        glClear(GL_COLOR_BUFFER_BIT);

    else {

        if (limparTela == 1) {
            glClear(GL_COLOR_BUFFER_BIT);
            printList();
            deleteList();
        }

        else {

            figLst *p = head;
            while (p != NULL) {

                glColor3fv(p->vColor);

                if (p->figure == LINE && numClick == 0)
                    drawLine(p);

                else if (p->figure == CIRC && numClick == 0)
                    drawCircumference(p);

                else if (p->figure == RETANGLE && numClick == 0)
                    drawRetangle(p);

                p = p->next;
            }
        }
    }
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

void changeToRetangleFig() {

    figure = RETANGLE;
    pos1[0] = pos1[1] = pos2[0] = pos2[1] = numClick = 0;
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

    if (last != NULL)
        last->vColor = vColor;

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

    if (last != NULL)
        last->espessura = espessura;

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
            setCoords(x, y, &pos1[0], &pos1[1]);
        }

        else {

            setCoords(x, y, &pos2[0], &pos2[1]);
            if (figure == CIRC)
                radius = sqrt(pow((pos2[0] - pos1[0]), 2) + pow((pos2[1] - pos1[1]), 2));

            addNode();
            limparTela = 0;
        }

        if (numClick > 0)
            numClick = 0;

        else {
            numClick += 1;
            start = 1;
            vColor = vColorBlack;
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
