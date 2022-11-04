/*
 *   UNIFESP SJC
 *
 *   COMPUTAÇÃO GRÁFICA
 *   OPENGL - FRACTAL - ÁRVORE DE PITÁGORAS
 *
 *   LUIZ GUSTAVO ALVES ASSIS DA SILVA
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

/* TAMANHO DA JANELA */
const int WIDTH = 1500, HEIGHT = 800;

/* PALETE DE CORES */
float vColorRed[] = {1.0, 0.0, 0.0};
float vColorOrange[] = {1.0, 0.5, 0.0};
float vColorLimeGreen[] = {0.196, 0.8, 0.196};
float vColorGreen[] = {0.0, 1.0, 0.0};
float vColorAquamarine[] = {0.439, 0.858, 0.576};
float vColorBlue[] = {0.0, 0.0, 1.0};
float vColorBlueViolet[] = {0.623, 0.372, 0.623};
float vColorPurple[] = {0.87, 0.58, 0.98};
float vColorMagenta[] = {1.0, 0.0, 1.0};
float vColorWhite[] = {1.0, 1.0, 1.0};

/* NÚMERO DE INTERAÇÕES */
int n;

/* DEFININDO DE STRUCTS */
typedef struct Coords {

    float px, py;

} Coords;

Coords a, b;

/* ESCOPO DAS FUNÇÕES */
void menu();
void initCoords();
void selectColor(int n);
void buildRectangle(Coords a, Coords b, Coords c, Coords d, int n);
void arvorePitagoras(Coords a, Coords b, int n);
void display();

void menu() {

    printf("* * * * * Arvore de Pitagoras * * * * *");

    int errFlag = 1;
    while (errFlag) {
        printf("\nInserir Numero de Interacoes: (LIMITE 15): ");
        scanf("%d", &n);
        if (n >= 0 && n <= 15) errFlag = 0;
    }
}

void initCoords() {
    a.px = 0.08;
    a.py = -0.08;
    b.px = -0.08;
    b.py = -0.08;
}

void selectColor(int n) {

    int color = n % 9;

    switch (color) {

        case 0:
            glColor3fv(vColorRed);
            break;

        case 1:
            glColor3fv(vColorOrange);
            break;

        case 2:
            glColor3fv(vColorLimeGreen);
            break;

        case 3:
            glColor3fv(vColorGreen);
            break;

        case 4:
            glColor3fv(vColorAquamarine);
            break;

        case 5:
            glColor3fv(vColorBlue);
            break;

        case 6:
            glColor3fv(vColorBlueViolet);
            break;

        case 7:
            glColor3fv(vColorPurple);
            break;

        case 8:
            glColor3fv(vColorMagenta);
            break;
    }
}

void buildRectangle(Coords a, Coords b, Coords c, Coords d, int n) {

    selectColor(n);
    glBegin(GL_POLYGON);

        glVertex2f(a.px, a.py);
        glVertex2f(b.px, b.py);
        glVertex2f(c.px, c.py);
        glVertex2f(d.px, d.py);

    glEnd();
}

void arvorePitagoras(Coords a, Coords b, int n) {

    Coords c, d, e;

    c.px = b.px - (a.py -  b.py);
	c.py = b.py - (b.px - a.px);

	d.px = a.px - (a.py -  b.py);
	d.py = a.py - (b.px - a.px);

	e.px = d.px + (b.px - a.px - (a.py -  b.py)) / 2;
	e.py = d.py - (b.px - a.px + a.py -  b.py) / 2;

    if (n >= 0) {

        buildRectangle(a, b, c, d, n);
        arvorePitagoras(d, e, n - 1);
        arvorePitagoras(e, c, n - 1);
    }
}

void display() {

    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    arvorePitagoras(a, b, n);
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {

    menu();
    initCoords();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Árvore de Pitágoras");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
 }
